#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// ������
namespace Settings {
const int MAX_LEN = 20;  // ���ִ���ʱ,��ʾ���������ݵ���󳤶�
const int CASE_CNT = 1000;                 // ���Ĳ��Դ���
const int BUFFER_SIZE = 1 << 10;          // ÿ�еĻ�������С
const char *const dataFile = "makedata.cpp";  // ����������ݵ�Դ�����ļ���
const char *const userFile = "user.cpp";  // ��Ҫ���Ե�Դ�����ļ���
const char *const stdFile = "std.cpp";    // ��׼�𰸵�Դ�����ļ���
const char *const dataExeName = "pai_data.exe";
const char *const userExeName = "pai_user.exe";
const char *const stdExeName = "pai_std.exe";
const char *const dataOutputName = "data.in";
const char *const userOutputName = "pai_user.txt";
const char *const stdOutputName = "data.out";
}  // namespace Settings

using namespace Settings;
using namespace std;

char cmd[BUFFER_SIZE], info[BUFFER_SIZE * 3];
char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];

template <typename... T>
int run(const char *str, T... args) {
    sprintf(cmd, str, args...);
    return system(cmd);
}

bool fileCompare(const char *stdOutput, const char *userOutput) {
    FILE *fp_std = fopen(stdOutput, "r"), *fp_user = fopen(userOutput, "r");
    if (fp_std == nullptr || fp_user == nullptr) {
        sprintf(info, "Open file failed: %s\n", strerror(errno));
        return false;
    }
    bool flag = true;
    for (int i = 1; !feof(fp_std) && !feof(fp_user); ++i) {
        char *p1 = fgets(buf1, BUFFER_SIZE, fp_std);
        char *p2 = fgets(buf2, BUFFER_SIZE, fp_user);
        if (p1 == nullptr && p2 == nullptr) {
            flag = true;
            break;
        } else {
            int len1 = p1 ? strlen(p1) : -1, len2 = p2 ? strlen(p2) : -1;
            if (p1 && p1[len1 - 1] == '\n') p1[len1 - 1] = 0, --len1;
            if (p2 && p2[len2 - 1] == '\n') p2[len2 - 1] = 0, --len2;
            if (p1 == nullptr || p2 == nullptr || len1 != len2 ||
                strcmp(p1, p2)) {
                
                if (len1 > MAX_LEN)
                    sprintf(p1 + MAX_LEN, "... (%d characters omitted)",
                            len1 - MAX_LEN);
                if (len2 > MAX_LEN)
                    sprintf(p2 + MAX_LEN, "... (%d characters omitted)",
                            len2 - MAX_LEN);
                sprintf(info,
                        "Difference found in line %d:\n  std: %s\n user: %s\n",
                        i, p1 ? p1 : "(EOF Detected)",
                        p2 ? p2 : "(EOF Detected)");
                flag = false;
                break;
            }
        }
    }
    fclose(fp_std), fclose(fp_user);
    return flag;
}

int main() {
    int totaltimeCnt = 0;
    printf("Compiling... ");
    if (run("g++ %s -std=c++11 -o %s", userFile, userExeName) ||
        run("g++ %s -std=c++11 -o %s", stdFile, stdExeName) ||
        run("g++ %s -std=c++11 -o %s", dataFile, dataExeName)) {
        puts("Compile failed.");
        printf("Press ENTER to exit.\n");
        getchar();
        return 0;
    }

    puts("Finished.");
    clock_t stUser, edUser, stStd, edStd;
    bool Accepted = true;
    for (int i = 1, ret; i <= CASE_CNT; ++i) {
        printf("Case %03d: ", i);
        run("%s >%s", dataExeName, dataOutputName);
        printf("getdata ok! ");
        // run std solution
        stStd = clock();
        ret = run("%s <%s >%s", stdExeName, dataOutputName, stdOutputName);
        edStd = clock();
        if (ret) {
            printf("Non Zero Exit Code: Std solution returned value %d\n", ret);
            Accepted = false;
            break;
        }

        // run user's solution
        stUser = clock();
        ret = run("%s <%s >%s", userExeName, dataOutputName, userOutputName);
        edUser = clock();
        if (ret) {
            printf("Non Zero Exit Code: User's solution returned value %d\n",
                   ret);
            Accepted = false;
            break;
        }

        if (!fileCompare(stdOutputName, userOutputName)) {
            printf("Wrong answer.\n------------------------------\n");
            printf("%s", info);
            printf("------------------------------\n");
            Accepted = false;
            break;
        }
        printf("Accepted. StdTime:%4d ms, UserTime:%4d ms\n",
               int(edStd - stStd), int(edUser - stUser));
        totaltimeCnt += int(edUser - stUser);
    }
    if (Accepted) {
        printf("\nUser's solution got accepted after %d tests.\n", CASE_CNT);
        printf("Average time spent: %.2f ms.\n",
               double(totaltimeCnt) / CASE_CNT);
    }
    printf("Press ENTER to exit.\n");
    getchar();
    return 0;
}

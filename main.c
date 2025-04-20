#define _GNU_SOURCE
#include <sched.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/mount.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define STACK_SIZE (1024 * 1024)  // 建立新行程所需的堆疊大小（1MB）
#define container_path "/root/container"

// 下載容器
int load_container(char *container_type, char *container_version, char *container_name) {
    char command[1024];  // 定義拼接的命令變數

    // 判斷容器類型並組合相應的命令
    if (strcmp(container_type, "debian") == 0) {
        snprintf(command, sizeof(command), "debootstrap --arch amd64 %s %s/%s http://deb.debian.org/debian", container_version, container_path, container_name);
    } else if (strcmp(container_type, "ubuntu") == 0) {
        snprintf(command, sizeof(command), "debootstrap --arch amd64 %s %s/%s http://archive.ubuntu.com/ubuntu", container_version, container_path, container_name);
    } else {
        // 當作業系統未知時，輸出錯誤信息
        fprintf(stderr, "不支援的作業系統: %s\n", container_type);
        return 1;
    }

    // 使用system()執行命令
    int return_value = system(command);

    // 檢查命令執行結果
    if (return_value == -1) {
        perror("system()失敗");
        return 1;
    }

    printf("debootstrap已成功執行，回傳碼: %d\n", return_value);
    return 0;
}

// 運行容器
int start_container(char *container_name) {
    printf("進入容器程序 PID = %d\n", getpid());

    // 設定容器內的hostname
    sethostname(container_name, strlen(container_name));

    // 拼接容器路徑
    char container_full_path[1024];
    snprintf(container_full_path, sizeof(container_full_path), "%s/%s", container_path, container_name);

    // 使用chroot切換根目錄到容器的
    if (chroot(container_full_path) != 0) {
        perror("chroot");  // 若失敗，顯示錯誤訊息
        exit(EXIT_FAILURE);
    }

    // 進入容器根目錄
    chdir("/");

    // 掛載/proc，讓ps、top等指令可使用
    mount("proc", "/proc", "proc", 0, "");

    // 執行bash
    char *const container_args[] = {"/bin/bash", NULL};
    execv(container_args[0], container_args);

    // 若execv失敗，印出錯誤訊息
    perror("execv");
    return 1;
}

// 移除容器
int delete_container(char *container_name) {
    char command[1024];  // 定義拼接的命令變數

    // 拼接移除容器指令
    snprintf(command, sizeof(command), "rm -rf %s/%s", container_path, container_name);

    // 使用system()執行命令
    int return_value2 = system(command);

    // 檢查命令執行結果
    if (return_value2 == -1) {
        perror("system()失敗");
        return 1;
    }

    printf("移除容器已成功執行，回傳碼: %d\n", return_value2);
    return 0;
}

// 主程式
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("使用方式: %s [--load <選擇debian或ubuntu作業系統> <選擇作業系統版本> <自訂container名稱>] [--start <自訂container名稱>] [--delete <自訂container名稱>]\n", argv[0]);
        return 1;
    }

    // 下載容器
    if (strcmp(argv[1], "--load") == 0) {
        return load_container(argv[2], argv[3], argv[4]);
    }

    // 運行容器
    if (strcmp(argv[1], "--start") == 0) {
        return start_container(argv[2]);
    }

    // 移除容器
    if (strcmp(argv[1], "--delete") == 0) {
        return delete_container(argv[2]);
    }
}
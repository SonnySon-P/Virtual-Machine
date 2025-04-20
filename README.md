# Homemade Virtual Machine

基於Linux核心打造簡易的Virtual Machine。

## 壹、基本說明
**一、目標：**
在我過去修讀作業系統課程時，教授曾經安排了一個練習，讓我們深入操作Linux核心的命名空間(namespace)，並透過C語言來實現容器的操作。這個練習讓我對操作系統底層機制、虛擬化技術以及容器的運作有了更為清晰的理解，也讓我意識到Linux核心的強大和靈活性。基於當時的回家作業經驗，並在此基礎上進行升級與擴展，模仿Docker的容器技術，開發一個簡單的虛擬機系統。具備基本功能，如載入與儲存映像檔、啟動並運行容器等操作。
<br>

**二、開發環境：**
以下是開發該平台所採用的環境：
* 虛擬機：Docker
* 映像檔：golang
* 程式語言：C
* 程式編輯器：Visual Studio Code

## 貳、操作說明
**一、安裝程式方式：** 
請在UNIX類系統(如Linux或macOS)中，來運行該程式，步驟如下：
***步驟1:*** 安裝debootstrap，作為未來下載ubuntu或debian（下載的是最小的完整ubuntu及debian作業系统）會使用到的套件。
```bash
apt update
apt install debootstrap
```

***步驟2:*** 編譯C，生成一個名為`main`的執行檔。
```bash
gcc -o main main.c
```

***步驟 3:*** 切換到root
```bash
su
```

**二、運行程式方式：**
1. 下載容器
```bash
./main --load <選擇debian或ubuntu作業系統> <選擇作業系統版本> <自訂container名稱>
```
支持的作業系统版本，Debian有stable、buster、bullseye，Ubuntu有focal、jammy、kinetic、lunar。

2. 啟動容器
```bash
./main --start <container名稱>
exit # 跳出容器
```

3. 移除容器（目前無法移除容器中的/proc虛擬檔案）
```bash
./main --delete <container名稱>
```

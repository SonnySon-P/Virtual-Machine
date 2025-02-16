# Homemade Virtual Machine

基於Linux核心打造的Virtual Machine。

## 壹、基本說明
**一、目標：**
在我過去修讀作業系統課程時，教授曾經安排了一個練習，讓我們深入操作Linux核心的命名空間(namespace)，並透過C語言來實現容器的操作。這個練習讓我對操作系統底層機制、虛擬化技術以及容器的運作有了更為清晰的理解，也讓我意識到Linux核心的強大和靈活性。基於當時的回家作業經驗，並在此基礎上進行升級與擴展，模仿Docker的容器技術，開發一個簡單的虛擬機系統。具備基本功能，如載入與儲存映像檔、啟動並運行容器等操作。
<br>

**二、開發環境：**
以下是開發該平台所採用的環境：
* 虛擬機：Docker
* 映像檔：golang
* 程式語言：Golang
* 程式編輯器：Visual Studio Code

**三、檔案說明：** 
此專案檔案（指coding這個資料夾）主要分為兩個資料夾：nodejs和tests。其中，nodejs資料夾為後端平台的主要程式碼，tests資料夾則存放使用jest框架進行的單元測試。接下來將對各資料夾中的檔案內容進行詳細說明。

## 貳、操作說明
**一、安裝程式方式：** 
**二、運行程式方式：**
```shell
vm -load <path>  // 載入映像檔，將指定的映像檔解壓到容器目錄中
vm -save <path>  // 將當前容器保存為新映像檔
vm -create <path>  // 從映像檔創建容器
vm -start <containerID>  // 啟動容器
vm -stop <containerID>  // 停止容器
vm -delete <containerID>  // 刪除容器
```

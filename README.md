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
```bash
.
├── LICENSE
├── README.md
└──  code  # 開發程式資料夾
      ├── main.py  # 主程式
      ├── readFile.py  # 讀取組語模組
      ├── RV32IMemory.py  # 模擬memory模組
      ├── RV32IRegisters.py  # 模擬register模組
      ├── cpuCore.py  # 模擬CPU模組
      ├── instructionTyple.py  # instruction與Typle的對應模組
      ├── rType.py  # 模擬R-Type instruction運行模組
      ├── iType.py  # 模擬I-Type instruction運行模組
      ├── sType.py  # 模擬S-Type instruction運行模組
      ├── bType.py  # 模擬B-Type instruction運行模組
      ├── uType.py  # 模擬U-Type instruction運行模組
      ├── jType.py  # 模擬J-Type instruction運行模組
      ├── otherType.py  # 模擬ecall instruction運行模組
      └── try.asm  # 測試檔案
```

## 貳、操作說明
**一、安裝程式方式：** 
將一個編譯好的執行檔放置到`bin`資料夾並設置好環境路徑，步驟如下：
***步驟1: 編譯Golang，生成一個名為`vm`的執行檔。
```bash
go build -o vm main.go
```

***步驟 2: 將執行檔放到`bin`資料夾
請在UNIX類系統(如Linux或macOS)中，將執行檔放到`/usr/local/bin`或`~/bin` 通常是用來存放可執行檔的目錄。
```bash
mkdir -p ~/bin
mv vm ~/bin/
```

***步驟 3: 設置環境路徑
接下來，您需要設置您的環境變數，使得系統可以找到您放置的`bin`資料夾。使得可以在任何地方執行`vm`。

1. 開啟`.bashrc`或`.zshrc`配置檔(取決於您使用的 shell)，如果使用的是`bash`，需要編輯`~/.bashrc`文件；如果使用的是`zsh`，則是`~/.zshrc`文件。
```bash
nano ~/.bashrc  # 如果是 bash
# 或者
nano ~/.zshrc   # 如果是 zsh
```

2. 添加`bin`資料夾到`$PATH`，在配置文件中，加入以下一行：
```bash
export PATH=$PATH:~/bin
```

**二、運行程式方式：**
```shell
vm -load <path>  // 載入映像檔，將指定的映像檔解壓到容器目錄中
vm -save <path>  // 將當前容器保存為新映像檔
vm -create <path>  // 從映像檔創建容器
vm -start <containerID>  // 啟動容器
vm -stop <containerID>  // 停止容器
vm -delete <containerID>  // 刪除容器
```

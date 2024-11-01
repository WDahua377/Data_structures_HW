## Minimum UAV Deployment Problem
### UAV Deployment
多個配置了物聯網（Internet of Things, IoT）設備的監控興趣點（Points of Interest, PoI）設置於野外以監控野火的發生，而無人機需要飛到這些設備附近蒐集數據，然而單一無人機的飛行時間有限，無法抵達所有 PoI，因此需要部屬多個無人機，並且優化無人機的巡視路線以最小化部屬的無人機數量。

### 程式目的
模擬無人機巡邏多個興趣點的位置配置，輸入物聯網設備的位置座標與無人機的最大飛行時間 B，優化無人機的巡視路線以盡量減少無人機的使用數量並蒐集到所有物聯網設備的數據，最後統計所使用的無人機數量並顯示每台無人機的巡視路線。

### 實作方法
使用 Kruskal’s algorithm 建立一個 Minimum Cost Spanning Tree，再依據 DFS（Depth First Search）的訪問順序創造一條遍歷所有節點的路徑，由於無人機需要回到起點，因此當 $$路徑長度 ＞ \frac{B}{2}$$ 則分割該路徑並配置一台無人機。

### 輸入
<li>格式</li>

```bash
#Nodes    B
    // 節點（興趣點）的數量與最大飛行時間 B

NodeID    CoordinateX    CoordinateY ...
    // NodeID 為節點（興趣點）的編號，隨後輸入的是節點（興趣點）的位置座標
``` 

<li>範例</li>

```bash
10 10
0 0.31943890 2.29615086
1 1.22727638 2.82131700
2 3.11475237 0.10137054
3 3.33213435 0.71334089
4 6.85464191 0.62696129
5 7.36465772 2.01343701
6 8.14020191 2.09479811
7 8.93059113 1.88562411
8 9.20708976 3.03945723
9 9.55529399 8.33022108
```

### 輸出
<li>格式</li>

```bash
#UAVs
    // 所使用的無人機總數
UAVID    1stNode    2ndNode    3rdNode ... lastNode
    // UAVID 為無人機的編號，接著顯示該無人機的巡邏路線
```  
<li>範例</li>

```bash
3 
0 0 1 3 2 
1 4 5 6 7 8 
2 9 
```

### 工具準備
<li>安裝 gcc：</li>

```bash
sudo apt-get install gcc
```
查看是否已安裝 gcc：`gcc --version`

### 編譯
```bash
gcc UAVpath.c -o UAVpath
```

### 執行
```bash
./UAVpath
```

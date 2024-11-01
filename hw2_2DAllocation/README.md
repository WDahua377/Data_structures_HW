## 2D Resource Allocation Problem with NR
### 2D Resource Allocation
將 5G NR 網路的無線資源以 2D 平面的形式分配，兩個維度分別是頻率和時間，使用者的需求可視為不同的頻率與時間所組成的平面矩形，而這些需求可以有數種候選形狀供替換。Basic Unit（BU） 資源最大化的分配模式，即在 BU 平面上填滿最多數量的矩形並且任何矩形之間不可重疊。

### 程式目的
模擬 5G NR 網路的無線資源分配，輸入 BU 的大小、多個使用者的 ID 與其候選形狀，計算 BU 資源可接受多少使用者的要求，統計可接受的使用者數量並顯示每位使用者所分配到（最左下角）的平面座標位置。

### 實作方法
對於所有使用者的要求，直接選定第一個候選形狀，依序將所有使用者的需求矩形在 BU 的最底端由左至右放入，放滿即不再接受使用者。（作業最低要求，以後可能會更換實作方法）

### 輸入
<li>格式</li>

```bash
ResourceY    ResourceX    #Users
    // Basic Unit 的大小（無線傳輸資源的數量）與使用者的數量

UserID    CandidateShape1    CandidateShape2 ...
    // UserID 為使用者的編號，隨後輸入的是使用者需求的所有候選形狀，如：4x4 2x8 1x16
``` 

<li>範例</li>

```bash
16 32 5
0 4x4 2x8
1 1x16
2 8x2 4x4 2x8
3 2x8 1x16
4 16x1 8x2 4x4 2x8 1x16
```

### 輸出
<li>格式</li>

```bash
#AcceptedUsers
    // 可滿足的使用者總數量
UserID   Usershape    PositionY    PositionX
    // ReqID 為被接受的使用者編號，接著顯示選擇放入的形狀以及放入位置
```  

<li>範例</li>
<br/>
<div align = "center">
<image src = "sample_graph.jpg">

範例輸出
</div>
<br/>


```bash
5
0 4x4 0 0
1 1x16 0 4
2 8x2 0 20
3 2x8 0 22
4 16x1 0 30
```

### 工具準備
<li>安裝 gcc：</li>

```bash
sudo apt-get install gcc
```
查看是否已安裝 gcc：`gcc --version`

### 編譯
```bash
gcc 2DAllocation.c -o 2DAllocation
```

### 執行
```bash
./2DAllocation
```

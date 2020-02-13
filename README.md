# Inverse Kinematics of Delta Robot

***

# 使い方 Usage

## ROSのワークスペースを作る（既にある場合は飛ばしてよい）
$ cd ~

$ mkdir -p your_ws_name/src 

$ cd your_ws_name/src 

$ catkin_init_workspace 


## catkin_makeでc+11コンパイラを有効化する
$ cd ~/your_ws_name 

$ sudo nano CMakeLists.txt 

CMakeLists.txtの上の方に1行追加する

```CMake
cmake_minimum_required(VERSION 2.8.3)

set(CATKIN_TOPLEVEL TRUE)

...
```

▽

```CMake
cmake_minimum_required(VERSION 2.8.3)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}") ##この行のように追記
set(CATKIN_TOPLEVEL TRUE)

...
```


## gitからcloneしてcatkin_makeをする
$ cd ~/your_ws_name/src 

$ git clone https://github.com/EaterK/delta_ik/tree/master/src 

$ cd ~/your_ws_name 

$ catkin_make 


## １つ目のターミナルで`roscore`を立ち上げる
$ roscore 


## ２つ目のターミナルで`delta_ik_node`を実行
$ rosrun delta_ik delta_ik_node


***
# 参考文献 Refference
1. http://forums.trossenrobotics.com/tutorials/introduction-129/delta-robot-kinematics-3276/
2. https://www.ohio.edu/mechanical-faculty/williams/html/pdf/DeltaKin.pdf
3. https://kurenaif.hatenablog.com/entry/2014/10/22/085354

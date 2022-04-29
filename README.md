# Stone
基于vcglib的Editor

# clone
```bash
git clone https://github.com/StoneHappy/Stone.git --recursive
```

## 依赖
你需要通过vcpkg安装osg、qt5和spdlog
```bash
vcpkg install qt5:x64-windows qt-advanced-docking-system:x64-windows
```

## 构建方法
```bash
cd Stone

mkdir build

cd build 

cmake ..

cmake --build ./ --config Release --target GU -j 10
```
# CMake Demo

This is a cmake demo project.

## Build and Install

1. Create a new directory for build artifacts

    ```bash
    mkdir build
    cd build
    ```

2. generate project files

    ```bash
    cmake ..
    ```

3. config project

    ```bash
    cmake-gui
    ```

    ![cmake-gui](/cmake-gui.jpg)

4. make and test

    ```bash
    make
    make test
    ```

5. install

    ```bash
    cpack -C CPackConfig.cmake
    ```

## License

[License](/License.txt)

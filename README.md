# seq_view
Describes an object which can refer to a sequence to which elements can be accessed with `operator []`.

Unlike `std::span`, data contiguity is not required and works with C++11.

For example, it accepts:
 - `std::vector`
 - `std::array`
 - user-defined class with `operator[]` and `size()`
 - C-style array
 - pointer to the first element and the number of elements

It also works with separate compilation because its size is constant.
  
## Essential commands
  - for conan 1.X
      ```
    conan install path/to/repo -pr:b=default -if path/to/build_dir -s build_type=Release
    conan build path/to/repo -bf path/to/build_dir
    ```
  - for conan 2.X
      ```
    conan build path/to/repo -pr:b=default -of path/to/build_dir -s build_type=Release
    ```

## Example
  - Windows Command Prompt
  - conan 1.61
  - In-source build
    ```
    mkdir .\build
    echo * > .\build\.gitignore
    conan install . -pr:b=default -if .\build -s build_type=Release
    conan build . -bf .\build
    ```

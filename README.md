# conan-example

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

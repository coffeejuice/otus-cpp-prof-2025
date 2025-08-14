# otus-cpp-prof-2025
OTUS C++ Prof training by Aleksandr Troshin

> ## Task
> ### Фильтрация IP-адресов
> Реализуем утилиту для эффективной сортировки и фильтрации лога IP-адресов. Продолжаем пользоваться сборочной фермой для публикации пакета.
> 
> Программа из стандартного ввода читает данные. Данные хранятся построчно. Каждая строка состоит из трех полей, разделенных одним символом табуляции, и завершается символом конца строки.
>
> Формат строки:
> - text1 \t text2 \t text3
>
> Поля text2 и text3 игнорируются. Поле text1 имеет следующую структуру (ip4 address):
> - n1.n2.n3.n4 где n1..4 – целое число от 0 до 255.
>
> Требуется загрузить список ip-адресов в память и отсортировать их в обратном лексикографическом порядке. 
> 
> Пример лексикографической сортировки (по первому числу, затем по второму и так далее):
> - 1.1.1.1 
> - 1.2.1.1 
> - 1.10.1.1
>
> Соответственно, обратная:
> - 1.10.1.1 
> - 1.2.1.1 
> - 1.1.1.1
>
> 💡 Обратите внимание – сортировка выполняется в байтовом (численном) представлении IP-адреса, а не в строковом. Поэтому адрес, например, 1.2.1.1 меньше адреса 1.10.1.1 (ведь 2 < 10).
>
> #### Далее выводим в стандартный вывод следующее:
> - Полный список адресов после сортировки. Одна строка - один адрес.
> - Сразу следом список адресов, первый байт которых равен 1. Порядок сортировки не меняется. Одна строка - один адрес. Списки ничем не разделяются.
> - Сразу продолжается список адресов, первый байт которых равен 46, а второй 70. Порядок сортировки не меняется. Одна строка - один адрес. Списки ничем не разделяются.
> - Сразу продолжается список адресов, любой байт которых равен 46. Порядок сортировки не меняется. Одна строка - один адрес. Списки ничем не разделяются.
>
> #### Требования к реализации
> - В приложенном к заданию исходном файле необходимо заменить, где это возможно, конструкции на аналогичные из стандарта С14/C17. 
> - Реализовать недостающий функционал. 
> - Не обязательно следовать приложенному шаблону. 
> - Можно выполнить задание, оформив код любым корректным способом.
>
> #### Лишний раз проверьте
> - лексикографическая сортировка понятна как для строки, так и для контейнера
> - выбрана соответствующая задаче структура данных
>
> #### Самопроверка
> - Макет исходного кода, а также тестовый файл с данными ip_filter.tsv прилагается к материалам занятия. Проверить себя можно следующим образом (Linux):
> - cat ip_filter.tsv | ip_filter | md5sum
> - 24e7a7b2270daee89c64d3ca5fb3da1a -
> 
> #### 💡Внимание! Из-за различного толкования символа
> - ’ на Linux и Windows, вышеприведенный хэш актуален только для Linux-систем.
> - В случае, если Ваша рабочая система Windows, придумайте способ, как проверить реализацию, имея эталонный результат только для Linux. 
> - Пакет ip_filter, содержащий исполняемый файл ip_filter, должен быть опубликован в качестве релиза в репозитории.
>
> ## Дополнительное упражнение
> Добавить unit-тесты для реализации на понравившемся тестовом framework-е (рекомендуем GoogleTest).

> ## List of Homework
> - Set up CI/CD


> ## Useful links
> - [S.Chacon, B.Straub Pro Git](https://git-scm.com/book/ru/v2)
> - [Connecting to GitHub with SSH](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)
> - [Bjarne Stroustrup's homepage](https://www.stroustrup.com/index.html)
> - [cPlusPlus.com](https://cplusplus.com/reference/)
> - [cppReference.com](https://en.cppreference.com/w/)
> - [Recursion](http://cppstudio.com/post/418/)
> - [How to mix C and C++](https://isocpp.org/wiki/faq/mixing-c-and-cpp)
> - [Efficient argument passing in C++11](https://www.codesynthesis.com/~boris/blog/2012/06/19/efficient-argument-passing-cxx11-part1/)
> - [Move semantics and rvalue references in C++11](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html)
> - [Windows PowerShell](https://ss64.com/ps/)
> - [*.cpp /D for #ifdef](https://learn.microsoft.com/en-us/cpp/build/reference/d-preprocessor-definitions?view=msvc-170&redirectedfrom=MSDN)
> - [Stroustrup. So, what's wrong with using macros?](https://www.stroustrup.com/bs_faq2.html#macro)
> - [Where is __dso_handle defined?](https://stackoverflow.com/questions/34308720/where-is-dso-handle-defined)
> - [isocpp.org: What is a reference?](https://isocpp.org/wiki/faq/references)
> - [Bost.Program_options - parsing command arguments](https://www.boost.org/doc/libs/1_58_0/doc/html/program_options.html)
> - [Спецификация на ключевое слово virtual](https://en.cppreference.com/w/cpp/language/virtual)
> - [Юнит-тестирование для чайников](https://habr.com/ru/post/169381/)
> - [Статья: Google testing framework (gtest)](https://habr.com/ru/articles/119090/)
> - [Алгоритм выбора STL-контейнера](https://habr.com/ru/companies/infopulse/articles/194726/)
> - [Михаил Матросов. Алгоритмы и итераторы](https://www.youtube.com/watch?v=UUuO6ry33as)
> - [Менеджер пакетов Conan для C++ проектов. Открытый вебинар OTUS](https://www.youtube.com/watch?v=Ny5BTWYHzWc)
> - [The Conan - C/C++ package manager](https://conan.io/center)
> - [VCPKG - C/C++ package manager](https://vcpkg.io/en/)

> ## Git commands
> ### Setup git on new PC
> - **git config --global user.email "alex.troshin@outlook.com"** - set email for the repository user
> - **git config --global user.name "Alex on Laptop"** - set nickname for the repository user
> ### New branch
> - **git checkout -b homework_01** - create new branch and switch to it (equivalent to **git branch homework_01** + **git checkout homework_01**)
> - **git push --set-upstream origin homework_01** - create in Github a remote branch "homework_01" and then upload 1st commits/versions to Github into the new remote branch
> ### New commit
> - **git add filename.ext** - ask git to watch the file "filename.ext"
> - **git commit -m "commit name"** - add new commit/version to the Git, assign commit's name "commit name"
> - **git commit -a -m "commit name"** - add all modified and deleted content and add new commit
> ### Remove files/dir from git
> - **git rm --cached -r somedir** - remove a dir from local git repo
> - **git rm --cached -r somefile.ext** - remove a file from local git repo
> ### Other
> - **git branch** - lists all branches, highlites current branch with *
> - **git brnch -d homework_01** - delete branch "homework_01"
> - **git push** - upload to Github the 2nd and foolowing commits
> - **git help git**, **git help -a** and **git help -g** - get help on Git commands and subcommands
> - **git checkout main** + **git merge homework_01** - switch to branch "main", then merge "homework_01" branch into "main" one
> ### Remote Branches
> - __git branch -r__ - Lists all the remote branches.
> - __git branch -r -v__ - Lists all the remote branches with the latest commit hash and commit message.
> - __git ls-remote__ - Lists all the references in the remote repository, including the branches.
> - __git remote show [remote_name]__ - Shows information about the specified remote, including the remote branches.
> - __git branch -a__ - Shows all the local and remote branches.

> ## Conan setup project
> ### Build new default profile (once after installing Conan)
> ```bash
> conan profile detect --force
> ```
> ### Conan file
> ```ini
> [requires]
> fmt/11.1.4
> 
> [generators]
> CMakeDeps
> CMakeToolchain
> 
> [layout]
> cmake_layout
> ```
> ### CMake file
> ```cmake
> cmake_minimum_required(VERSION 3.24)
> project(format)
> find_package(fmt REQUIRED)
> add_executable(${PROJECT_NAME} format.cpp)
> target_link_libraries(${PROJECT_NAME} fmt::fmt)
> set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
>```
> ### Set up project
> ```bash
> conan install . --output-folder=build/conan --build=missing
> ```
> ### Enable CMake Profile 'conan-release' 
> Profile enable/disable in Settings>Build, Execution, Deployment>CMake


> ## Shell commands
> - **ls -la** - list directory content including hidden one
> - **touch filename.ext** - create empty text file "filename.ext"

> ## VScode setup
> - [Install VSCode](https://code.visualstudio.com/docs/setup/windows#_install-vs-code-on-windows)
> - [Configure VS Code for Microsoft C++](https://code.visualstudio.com/docs/cpp/config-msvc)
> - Run 'Developer Command Prompt for Visual Studio'
> - Type in 'code' to open VSCode in the folder

> ## CMake setup
> - [Install CMake](https://cmake.org/download/)


> ## Connecting Google Testing Framework using Git
> ```bash
> git submodule init
> git submodule add https://github.com/google/googletest googletest
> git config -f .gitmodules submodule.googletest.branch v1.13.x
> git submodule update --remote
> ```

> ## When cloning repo with Google Testing Framework do following
> ```bash
> git submodule update --init --recursive
> ```



> ## References 
> ```c++
> void swap(int& i, int& j)
> {
>   int tmp = i;
>   i = j;
>   j = tmp;
> }
> int main()
> {
>   int x, y;
>   // ...
>   swap(x,y);
>   // ...
> }
>
>
> int a;
> int* v; # we CAN initialize address v
> v = &a; # v is address where a is stored 
> int& ref == *v; # ref is alias of a
> int* t = v + 1; t is address of the next cell
> 
>
> # Now we chan change address v, so v will point to another variable
>
> int b;
> v = &b; # v is address where b is stored 
> ```

# Programming system AIO (In developing)
![image](https://user-images.githubusercontent.com/22048950/46574135-a46b0a80-c9a7-11e8-8a0b-ade9160b7970.png)
# What is AIO?
### AIO is a object oriented programming language fused to write code more laconic and readable. 
# Base language:
## I. Variables
### a.) Auto type
#### 1.) Constant:
![image](https://user-images.githubusercontent.com/22048950/46576434-fe80c580-c9d1-11e8-98c4-75ba4227b41f.png)
#### 2.) Mutable:
![image](https://user-images.githubusercontent.com/22048950/46576450-3e47ad00-c9d2-11e8-9c41-9a8d7c443c61.png)
### b.) Explicit type
![image](https://user-images.githubusercontent.com/22048950/46576473-e493b280-c9d2-11e8-8ba9-8d4f12fb565e.png)
### c.) Null
![image](https://user-images.githubusercontent.com/22048950/46576491-5e2ba080-c9d3-11e8-9f73-ee6eec8a8909.png)
## II. If
### a.) Trivial
![image](https://user-images.githubusercontent.com/22048950/46580197-f142f580-ca28-11e8-952e-4ba8b8da3e5f.png)
### b.) With else branch
![image](https://user-images.githubusercontent.com/22048950/46580185-c35db100-ca28-11e8-89f6-d998f37c3147.png)
## III. For
![image](https://user-images.githubusercontent.com/22048950/46580270-50553a00-ca2a-11e8-857d-24bf86d699ce.png)
### Other description will appear later... 
## IV. When
![image](https://user-images.githubusercontent.com/22048950/46580328-5697e600-ca2b-11e8-8a3e-2371fdb7c943.png)
## V. Function
![image](https://user-images.githubusercontent.com/22048950/46580685-40d9ef00-ca32-11e8-9022-116695e0bdd6.png)
## VI. Class
### a.) Trivial
![image](https://user-images.githubusercontent.com/22048950/46580474-0706e980-ca2e-11e8-8d40-0915ffd1dcbb.png)
### b.) Several constructors
![image](https://user-images.githubusercontent.com/22048950/46580498-52b99300-ca2e-11e8-9ce9-5c0eaf954021.png)
### c.) Abstract class
![image](https://user-images.githubusercontent.com/22048950/46580550-bc866c80-ca2f-11e8-9175-6acf68ad6e95.png)
### d.) Inheritance
#### 1.) Single:
![image](https://user-images.githubusercontent.com/22048950/46580550-bc866c80-ca2f-11e8-9175-6acf68ad6e95.png)
#
![image](https://user-images.githubusercontent.com/22048950/46580672-f193be80-ca31-11e8-85e6-0232b704c142.png)
# Configure and launch
![image](https://user-images.githubusercontent.com/22048950/46580824-d5dde780-ca34-11e8-97a4-cf5770d301e7.png)
#### The main idea of creating language is to write and configure your project by AIO. It means there are two groups of *.aio files. The first group is a project file group (like a pure project). The second group is a config file group (like a Gradle script or CMakeLists). The code structure of these groups are identical. So, you can configure you project by writing settings in the config files and using AIOApi. 
#### AIOApi allows to change the structure of aio files that are written in the project.
![image](https://user-images.githubusercontent.com/22048950/46580816-a8913980-ca34-11e8-8340-6d6d7cf25662.png)
#### Thus, you can customize your project: make platform or framework. It can be used for big projects, services and games.

# AIOLifeCycle: Composing -> Configuring -> Running
![image](https://user-images.githubusercontent.com/22048950/46583576-012afb80-ca62-11e8-8f48-3df0151b2a87.png)
#### Firstly the program creates the AIOCore.
#### Next takes the first argument, the path to the folder with aio files, and runs a scanner that detects all aio files, and puts in AIOCore. 
#### If the program args have path to the modules using the flag "-m" (aio folder, or file), the program similarly scans the modules.
#### AIOModule is a class that has access to modify the files maintained this module in the build process of the AIOCore. You can inherit from AIOModule and write your own class that will have access to all such files. 
#### When you have finished assembling files and modules, the AIOCore will create instances of aio modules and using them. AIOCore will embed the instructions in your project files according imported AIOModules in each file by AIOApi.
#### After injecting creates AIOExecutable, program runtime. AIOExecutable gets compiled AIOCore, function file path and function name from program args and launches the function.

# Examples
## Custom testing
![image](https://user-images.githubusercontent.com/22048950/46582176-cc13ae80-ca4b-11e8-805d-c72c0914c25e.png)
#
![image](https://user-images.githubusercontent.com/22048950/46582189-e9487d00-ca4b-11e8-97c8-16427cc79ff8.png)

# T3 Profiling Framework

## Eclipse setup

1. Create a new managed C/C++ project
2. Get the framework into the project folder:
```
cd eclipse-project-folder
git init
git remote add origin git@github.com:tiludwig/prof-port.git
git pull -t origin master
```
3. In eclipse click refresh in your created project

You also need to configure the include path for the project:
Project Settings->C++ Build->Settings->GCC C++ Compiler->Includes add **${workspace_loc:/${ProjName}/T3Framework}**

## Port to different target architectures
You need to adapt three components (under T3Framework/Components)
- The communication driver used to communicate with the host application (Driver/Communication). You need to implement the CommunicationDriver interface
- The execution timer module, which is used to measure the actual execution time of the target. You need to implement the ExecutionTimer interface
- The target module, which serves as an adapter to the actual target. You need to implement the TargetWrapper interface

The framework is accessable by the frameworkEntryPoint(...) function in the T3Framework/framework.cpp file. In your main, create a communication driver, an execution timer and a target and pass these to the framework.
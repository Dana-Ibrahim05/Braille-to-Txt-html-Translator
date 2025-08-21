## Observations
Here are some observations I made while coding that I am a little confused about:
1. When creating any functions that take in fstream parameters, their implementation works only when I pass in these parameters by reference and consequently change the original function definition. Is there a particular reason for that?
This is because fstream is an interface that allows us to interact with files outside of our code. The thing is: the fstream library is system-dependent. Windows does not allow the modification of multiple files. Therefore you must pass in the fstream file by reference.

2. It seems that using pointers makes working with any functions that have fstream parameters a lot easier. Is this the case?

## Qiuestions
1. Should I have a distructor?

Yes, A distructor is important to avoid any potential errors such as the locking of files by the operating system.

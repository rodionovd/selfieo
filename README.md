Tiny lib that dumps in-memory image of the current process to a file.  

> Just a PoC, untested and dirty, so feel free not to use it in production.  

### Usage

1. Compile the library, put `libselfieo.dylib` into your current directory;  
2. Run your target using this command:  

  ```bash
$ DYLD_INSERT_LIBRARIES=libselfieo.dylib /Applications/mytarget.app/Contents/MacOS/mytarget
  ```  
  
  
------
🔓
If you found any bug(s) or something, please open an issue or a pull request — I'd appreciate your help!  
`(^,,^)`

------

*Dmitry Rodionov, 2014*
*i.am.rodionovd@gmail.com*
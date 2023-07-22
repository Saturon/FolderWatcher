To start folderwatcher
Example: python FolderWatcher -test D:\Games D:\Games\Folder1\Folder2 D:\Games\sadfasdfgadrewrgv
In this example we start watch over 3 folders. But you can start it for single if you want. 

If you want you can start c++ app only: 
Folderwatcher.exe D:\Games

Known problems:
1) Ctrl+C will memory leak and leave test folders in place
2) Starting watch over parent/child folder will cause log of D:\Games\Folder1 to be unreadable  (Example: D:\Games and D:\Games\Folder1)

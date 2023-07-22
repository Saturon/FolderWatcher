import sys, os, time, signal
import subprocess, _thread
from subprocess import PIPE, Popen
from pynput.keyboard import Key, Listener
import logging

#  
#  Example of command
#  python FolderWatcher -test D:\Games D:\Games\Tarkov D:\Games\sadfasdfgadrewrgv

def on_press(key):
    #print('{0} pressed'.format(key))
    if (key == Key.f12):
    	return False

def handler(signum, frame):
	print("Interrupted")
	#IDK. Memory leak + Interrupted tests
	exit(1)

def FLWS(str1) -> subprocess:
	result = subprocess.Popen([os.getcwd() + "/FolderWatcher/x64/Debug/Folderwatcher.exe", str1], close_fds=True, text=True)
	while True:
		with Listener(on_press=on_press) as listener:
			listener.join()
			if not listener.running:
				break
	
	result.send_signal(signal.SIGTERM)
	print(str1 + ' watch ended')
	

#######################################################
#######################################################
#######################################################

print(__name__ + ' started')
output = "Output: \n"

RunTests = False
if '-test' in sys.argv:
    print('Test started')
    sys.argv.remove('-test')
    RunTests = True
if '-t' in sys.argv:
    print('Test started')
    sys.argv.remove('-t')
    RunTests = True

if len(sys.argv[1:]) == 0:
	print("Add folder to command!")
	exit(1)

for path1 in sys.argv[1:]:
	if os.path.isdir(path1):
		try:
			print(path1 + ' watch started')
			s = _thread.start_new_thread(FLWS, (path1, ))
			print("Press F12 to stop programm...")
			if RunTests == True:
				pathtest = path1
		except:
			print("Error: unable to start thread!")
	else:
		print("Directory doesnt exist!", path1)

# Unreadable logging when watching included folders a-la D:/Games D:/Games/Folder1
time.sleep(5)
while True:
	if RunTests == True:
			os.mkdir(pathtest+"/test")
			time.sleep(1)
			os.rmdir(pathtest+"/test")
	with Listener(on_press=on_press) as listener:
		listener.join()
		if not listener.running:
			time.sleep(1) #Making sure to turn off process before thread
			break

_thread.exit() #Turn off all threads after processes
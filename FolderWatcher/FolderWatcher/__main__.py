import sys, os, time, signal
import subprocess, _thread
from subprocess import PIPE, Popen
from pynput.keyboard import Key, Listener
import logging

#  
#  Example of command
#  python FolderWatcher -test D:\Games D:\Games\sadfasdfgadrewrgv

def on_press(key):
    #print('{0} pressed'.format(key))
    if (key == Key.f12):
    	return False

def handler(signum, frame):
	print("Interrupted. Shutting down.")
	exit(1)

def FLWS(str1, tests, itest) -> subprocess:
	print(os.getcwd())
	result = subprocess.Popen([os.getcwd() + "/FolderWatcher/FolderWatcher.exe", str1], close_fds=True, text=True)

	if tests:
		print('Tests will start')
		os.mkdir(str1+"/testfolder" + str(itest)) # Test folder with path number
		time.sleep(1)
		os.rmdir(str1+"/testfolder" + str(itest))
		print('Tests ended')

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
signal.signal(signal.SIGINT, handler)

RunTests = False
if '-test' in sys.argv:
    sys.argv.remove('-test')
    RunTests = True
if '-t' in sys.argv:
    sys.argv.remove('-t')
    RunTests = True

if len(sys.argv[1:]) == 0:
	print("Add folder to command!")
	exit(1)

itest = 0
for path1 in sys.argv[1:]:
	if os.path.isdir(path1):
		try:
			print(path1 + ' watch started')
			s = _thread.start_new_thread(FLWS, (path1, RunTests, itest))
			print("Press F12 to stop programm...")
			itest += 1
		except:
			print("Error: unable to start thread!")
	else:
		print("Directory doesnt exist!", path1)
			
# Unreadable logging when watching included folders a-la D:/Games D:/Games/Folder1
while True:
	with Listener(on_press=on_press) as listener:
		listener.join()
		if not listener.running:
			time.sleep(1) #Making sure to turn off process before thread
			break

_thread.exit() #Turn off all threads after processes
exit(0)
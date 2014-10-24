import sys
import os
import shutil
import time

def help():
	print "USAGE: python <Program> no param"

if __name__ == "__main__":
	if 1 != len(sys.argv):
		help()
		sys.exit(-1)
	dump_file_name = 'C:\\dumps\\'
	dump_ge_name = 'C:\\ie.dmp'
	while 1:
		time.sleep(4)
		if os.path.exists(dump_ge_name):
			cur_time = time.strftime('%Y-%m-%d-%H-%M-%S',time.localtime(time.time()))
			print cur_time
			dump_file_name += cur_time
			dump_file_name += '.dmp'
			shutil.copy(dump_ge_name, dump_file_name)
			os.remove(dump_ge_name)
			os.system('taskkill /im windbg.exe')
		os.system('taskkill /im iexplore.exe')

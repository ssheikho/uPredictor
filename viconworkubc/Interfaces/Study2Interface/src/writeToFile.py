from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys
import time

class WriteToFile():
    def __init__(self, metafile):
        super().__init__()

        #self.metafile = open("metadata.txt", 'r')
        self.metafile = metafile
        self.partno = int(self.metafile.readline()) + 1
        self.metafile.close()

        self.metafile = open("metadata.txt", 'w')
        self.metafile.write(str(self.partno))
        self.metafile.close()

        self.filename = "part_" + str(self.partno) + ".txt"
        self.file = open(self.filename, 'w')

        self.file.write("Participant #: %d \n" % (self.partno))
        self.file.write("Time #: %s  \n" % (datetime.datetime.now().__str__()))
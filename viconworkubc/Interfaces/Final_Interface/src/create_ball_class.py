from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys
import time


class Create_balls():
    def __init__(self, nsteps):
        super().__init__()
        self.current_step = -2
        self.n_rounds = 0
        self.timestamp = time.time()
        self.finaltime = []
        self.nsteps = nsteps
        for i in range(0, self.nsteps + 1):
            self.finaltime.append("0")
        #self.reroll(outfile)
        #self.posCol = [0, 0, 0, 0]]

    def endroll(self, outfile):
        for i in range(0, self.nsteps):
            outfile.write("[" + str(i) + "]: " + self.finaltime[i].__str__() + "\n")
        outfile.write("END: " + (self.n_rounds - 1).__str__() + "\n")
        outfile.write("START: " + self.n_rounds.__str__() + "\n")

    def reroll(self, outfile):
        self.from_ramp = self.combi_colors()
        self.to_rack = self.combi()
        self.from_rack = self.combi()
        self.to_basket = self.combi()
        self.timestamp = time.time()


        outfile.write("Timestamp:\n")
        outfile.write(self.timestamp.__str__() + "\n")
        outfile.write("from_ramp:\n")
        outfile.write(self.from_ramp.__str__() + "\n")
        outfile.write("to_rack:\n")
        outfile.write(self.to_rack.__str__() + "\n")
        outfile.write("from_rack:\n")
        outfile.write(self.from_rack.__str__() + "\n")
        outfile.write("to_basket:\n")
        outfile.write(self.to_basket.__str__() + "\n")

        self.n_rounds += 1

    def print_info(self):
        self.print_combo(self.to_rack)
        self.print_combo(self.from_rack)
        self.print_combo(self.to_basket)
        self.print_combo(self.from_ramp)

    def combi(self):
        p = [0, 1, 2, 3]
        N = random.sample(p, 4)
        return N

    def combi_colors(self):
        p = [0, 1, 2, 3, 4]
        N = random.sample(p, 4)

        return N

    def print_combo(self, a):
        for i in range(0,4):
            print("%d "% a[i], end="")
        print(end="\n")

    def print_colors(self, a):
        for i in range(0,5):
            print("%d "% a[i], end="")
        print(end="\n")
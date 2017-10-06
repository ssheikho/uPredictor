from PyQt4.QtCore import *
from PyQt4.QtGui import *

import datetime
import random
import sys
import time

class Balls():
    def __init__(self, partno, nballspercol, nrounds):
        super().__init__()
        self.filename = "part_" + str(partno) + ".txt"
        self.file = open(self.filename, 'w')

        self.file.write("Participant #: " + partno.__str__() + "\n")
        self.file.write("Time #: " + datetime.datetime.now().__str__() + "\n")

        self.nrackslots = 9
        self.nballspercol = nballspercol
        self.ntimesteps = 22
        self.nrounds = nrounds

        self.current_step = -2
        self.current_round = -1
        self.task_step = 0

        self.ball_colors = ['black', 'orange', 'blue', 'red', 'purple', 'yellow']

        self.reroll()

    def endroll(self):
        for i in range(0, self.ntimesteps):
            self.file.write("[" + str(i) + "]: " + self.finaltime[i].__str__() + "\n")
        self.file.flush()

    def resetTimestamps(self):
        self.finaltime = []
        for i in range(0, self.ntimesteps + 1):
            self.finaltime.append("0")

    def reroll(self):
        self.resetTimestamps()

        self.from_ramp = self.from_ramp_combo()
        self.to_rack = self.rack_combo()
        self.from_rack = self.rack_combo()
        self.to_basket = self.rack_combo()
        self.one_ball_basket = random.randint(0,2)
        timestamp = time.time()
        self.current_round += 1
        self.task_step = 0

        self.file.write("Timestamp: " + timestamp.__str__() + "\n")
        self.file.write("current_round: " + self.current_round.__str__() + "\n")
        self.file.write("one_ball_basket: " + self.one_ball_basket.__str__() + "\n")
        self.file.write("from_ramp: " + self.from_ramp.__str__() + "\n")
        self.file.write("to_rack: " + self.to_rack.__str__() + "\n")
        self.file.write("from_rack: " + self.from_rack.__str__() + "\n")
        self.file.write("to_basket: " + self.to_basket.__str__() + "\n")
        self.file.write("task_step: " + self.task_step.__str__() + "  " + timestamp.__str__() + "\n")

        self.file.flush()

    def nextStep(self):
        timestamp = time.time()
        self.finaltime[self.task_step] = timestamp
        self.task_step = self.task_step + 1 if self.task_step < 22 else 22
        self.file.write("next_step: " + timestamp.__str__() + "\n")
        self.file.flush()
        return self.task_step

    def backStep(self):
        timestamp = time.time()
        self.task_step = self.task_step - 1 if self.task_step > 0 else 0
        self.file.write("back_step: " + timestamp.__str__() + "\n")
        self.file.flush()
        return self.task_step

    def nextRound(self):
        timestamp = time.time()
        self.file.write("next_round: " + timestamp.__str__() + "\n")
        self.file.flush()
        if self.task_step == 22:
            self.endroll()
            self.reroll()
        return self.task_step

    def thisIsTheFinalRound(self):
        return self.current_round == (self.nrounds - 1)

    def gameDone(self):
        return self.thisIsTheFinalRound() & (self.task_step == 22)

    def print_info(self):
        self.print_combo(self.from_ramp, 9)
        self.print_combo(self.to_rack, 9)
        self.print_combo(self.from_rack, 9)
        self.print_combo(self.to_basket, 9)

    def rack_combo(self):
        p = []
        for i in range(0,self.nrackslots):
            p.append(i)
        N = random.sample(p, self.nrackslots)
        return N

    def from_ramp_combo(self):
        p = []
        for column in range(0,5):
            for row in range(0,self.nballspercol + 1):
                p.append(column)
        N = random.sample(p, self.nrackslots)

        return N

    def print_combo(self, a, nItems):
        for i in range(0,nItems):
            print("%d "% a[i], end="")
        print(end="\n")
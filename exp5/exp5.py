import copy
import re
import sndhdr
from traceback import print_tb
global_msg = []
# time,msg,sender,receiver
dnodes = []
prop_delay = 2
exec_time = 2
n = 5
class Node:
    id = 0 
    sv = []
    sn = []
    tsv = []
    tsn = []
    no_of_nodes = 0
    execute_cs_till = float("inf")
    def __init__(self, id, no_of_nodes):
        self.id = id
        self.no_of_nodes = no_of_nodes
        self.sn = [0 for i in range(no_of_nodes)]
        self.tsn = [0 for i in range(no_of_nodes)]
        self.sv = [ "R" if i<=self.id else "N" for i in range(no_of_nodes)]
        self.tsv = ["N" for i in range(no_of_nodes)]
    
    def receive_msg(self, msg):
        time,mssg,sender,receiver = msg
        if mssg == "token":
            print(f"Node {self.id} is entering the CS")
            self.tsv = dnodes[sender].tsv
            self.tsn = dnodes[sender].tsn
            self.sv[self.id] = "E"
            self.execute_cs_till = time + exec_time
        elif mssg == "request":
            sender_node = dnodes[sender]
            receiver_node = dnodes[receiver]
            if sender_node.sn[sender] <= receiver_node.sn[sender]:
                return 
            receiver_node.sn[sender] = sender_node.sn[sender]
            if receiver_node.sv[receiver] == "N":
                receiver_node.sv[sender] = "R"
            elif receiver_node.sv[receiver] == "R":
                if receiver_node.sv[sender] != "R":
                    receiver_node.sv[sender] = "R"
                    send_msg([time,"request" , self.id, sender])
            elif receiver_node.sv[receiver] == "E":
                receiver_node.sv[sender] = "R"
            elif receiver_node.sv[receiver] == "H":
                receiver_node.sv[receiver] = "N"
                receiver_node.sv[sender] = "R"
                self.tsv[sender] = "R"
                self.tsn[sender] = sender_node.sn[sender]
                sender_node.tsv = self.tsv
                sender_node.tsn = self.tsn
                send_msg([time,"token",self.id,sender])

    def handle_cs_exec(self, time):
        if self.execute_cs_till <= time:
            print(f"Node {self.id} is exiting the CS")
            self.execute_cs_till = float("inf")
            self.sv[self.id] = "N"
            self.tsv[self.id] = "N"
            for j in range(self.no_of_nodes):
                if self.sn[j] > self.tsn[j]:
                    self.tsv[j] = self.sv[j]
                    self.tsn[j] = self.sn[j]
                else:
                    self.sv[j] = self.tsv[j]
                    self.sn[j] = self.tsn[j]
            if self.sv.count("N") == self.no_of_nodes:
                self.sv[self.id] = "H"
            else:
                r = self.sv.index("R")
                send_msg([time,"token",self.id,r])

    def request_token(self, time):
        if self.sv[self.id] == "H":
            self.execute_cs_till = time + exec_time
            print(f"Node {self.id} is entering in cs")
            return 
        self.sn[self.id] += 1 
        for i in range(self.no_of_nodes):
            if i != self.id and self.sv[i] == "R":
                send_msg([time,"request" , self.id, i])
    
def send_msg(msg):
    global global_msg, prop_delay
    msg2 = copy.deepcopy(msg)
    msg2[0] += prop_delay
    global_msg.append(msg2)

def step(time):
    global global_msg
    temp = []
    for gm in global_msg:
        if gm[0] <= time :
            print(f"Node {gm[3]} has received message {gm[1]} from node {gm[2]}")
            dnodes[gm[3]].receive_msg(gm)
        else:
            temp.append(gm)
    global_msg = temp
    for i in dnodes:
        i.handle_cs_exec(time)


dnodes = [Node(i,n) for i in range(n)]
dnodes[0].sv[0]="H"
for time in range(0,100):
    print()
    print("current time is ",time)
    print()
    query= input("press 0 to perform operation or 1 to continue ")
    if query == "0":
        csnode = input("enter node that wants to enter cs ")
        dnodes[int(csnode)].request_token(time)
    print(global_msg)
    step(time)
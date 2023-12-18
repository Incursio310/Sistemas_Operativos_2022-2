import threading
import random
import time
import os
from datetime import datetime


LockLobby = threading.Lock()
LockEstandar = threading.Lock()
LockVersus = threading.Lock()
LockRapida = threading.Lock()
LockNavidad = threading.Lock()

CVEstandar = threading.Condition(LockLobby)
CVVersus = threading.Condition(LockLobby)
CVRapida = threading.Condition(LockLobby)
CVNavidad = threading.Condition(LockLobby)

Estandar_full = threading.Semaphore(0)
Estandar_empty = threading.Semaphore(15)
Estandar_mutex = threading.Semaphore(1)

Versus_full = threading.Semaphore(0)
Versus_empty = threading.Semaphore(2)
Versus_mutex = threading.Semaphore(1)

Rapida_full = threading.Semaphore(0)
Rapida_empty = threading.Semaphore(10)
Rapida_mutex = threading.Semaphore(1)

Navidad_full = threading.Semaphore(0)
Navidad_empty = threading.Semaphore(12)
Navidad_mutex = threading.Semaphore(1)

PartidaEstandar = []
ColaEstandar = []
EsperaEstandar = []
MAXEstandar = 7

PartidaVersus = []
ColaVersus = []
EsperaVersus = []
MAXVersus = 4

PartidaRapida = []
ColaRapida = []
EsperaRapida = []
MAXRapida = 8

PartidaNavidad = []
ColaNavidad = []
EsperaNavidad = []
MAXNavidad = 10

def Estandar():
    LockLobby.acquire()
    archOut = open("Salida.txt", "a")
    for i in range(len(PartidaEstandar)):
        Estandar_full.acquire()
        Estandar_mutex.acquire()
        Jugador = PartidaEstandar.pop(0)

        Salida = datetime.now()
        Salida = Salida.strftime("%H:%M:%S.%f")

        #archOut.write("Jugador"+str(Jugador)+", "+Salida+"\n")
        archOut.write("Jugador {}, {}\n".format(str(Jugador), Salida))
        Estandar_mutex.release()
        Estandar_empty.release()

    CVEstandar.notify_all()
    archOut.close()

        #Antes o despues de notificar, hago la wea de los archivos. Importante guardar el elemento en la posicion 0 antes de hacer pop.
    #print("----Estandar terminada----")
    LockLobby.release()

def Versus():
    LockLobby.acquire()
    archOut = open("Salida.txt", "a")
    for i in range(len(PartidaVersus)):

        
        Versus_full.acquire()
        Versus_mutex.acquire()
        Jugador = PartidaVersus.pop(0)

        Salida = datetime.now()
        Salida = Salida.strftime("%H:%M:%S.%f")

        #archOut.write("Jugador"+str(Jugador)+", "+Salida+"\n")
        archOut.write("Jugador {}, {}\n".format(str(Jugador), Salida))
        Versus_mutex.release()
        Versus_empty.release()
        

    archOut.close()

    CVVersus.notify_all()
    #print("----Versus terminada----")
    LockLobby.release()

def Rapida():
    LockLobby.acquire()
    archOut = open("Salida.txt", "a")
    for i in range(len(PartidaRapida)):
        Rapida_full.acquire()
        Rapida_mutex.acquire()
        Jugador = PartidaRapida.pop(0)

        Salida = datetime.now()
        Salida = Salida.strftime("%H:%M:%S.%f")

        #archOut.write("Jugador"+str(Jugador)+", "+Salida+"\n")
        archOut.write("Jugador {}, {}\n".format(str(Jugador), Salida))
        Rapida_mutex.release()
        Rapida_empty.release()

    CVRapida.notify_all()
    archOut.close()
    #print("----Rapida terminada----")
    LockLobby.release()

def Navidad():
    LockLobby.acquire()
    archOut = open("Salida.txt", "a")
    for i in range(len(PartidaNavidad)):
        Navidad_full.acquire()
        Navidad_mutex.acquire()
        Jugador = PartidaNavidad.pop(0)

        Salida = datetime.now()
        Salida = Salida.strftime("%H:%M:%S.%f")

        #archOut.write("Jugador"+str(Jugador)+", "+Salida+"\n")
        archOut.write("Jugador {}, {}\n".format(str(Jugador), Salida))
        Navidad_mutex.release()
        Navidad_empty.release()

    CVNavidad.notify_all()

    #print("----Navidad terminada----")
    LockLobby.release()

def lobby(cola, num):
    LockLobby.acquire()
    #entradaLobby[num-1] = now.strftime("%H:%M:%S")
    entradaLobby = datetime.now()
    entradaLobby = entradaLobby.strftime("%H:%M:%S.%f")
    #print("Buscando cola: ", cola, "para jugador", num)
    
    if cola == 0: #Partida estándar
        while(len(ColaEstandar) == MAXEstandar):
            if num not in EsperaEstandar:
                EsperaEstandar.append(num)
            CVEstandar.wait()

        primeroES = False
        if(len(EsperaEstandar) > 0):
            if(EsperaEstandar[0] == num):
                primeroES = True
            #print(".......primeroES......: ", primeroES)
            
            while(len(ColaEstandar) == MAXEstandar or primeroES == False):
                CVEstandar.wait()
                if(EsperaEstandar[0] == num):
                    primeroES = True
        
        ColaEstandar.append(num)

        entradaCola = datetime.now()
        entradaCola = entradaCola.strftime("%H:%M:%S.%f")

        arch = open("Lobby.txt", "a")
        #s = "Jugador{0}, {1}, Partida Estandar, {2}\n"

        arch.write("Jugador{0}, {1}, Partida Estandar, {2}\n".format(num, entradaLobby, entradaCola))

        arch.close()

        LockLobby.release()

        Estandar_empty.acquire()
        Estandar_mutex.acquire()

        LockEstandar.acquire()

        ColaEstandar.pop(0)
        PartidaEstandar.append(num)

        entradaPartidaES = datetime.now()
        entradaPartidaES = entradaPartidaES.strftime("%H:%M:%S.%f")

        archEs = open("PartidaEstandar.txt", "a")
        #sES = "Jugador{0}, {1}, {2}\n"
        archEs.write("Jugador{0}, {1}, {2}\n".format(num, entradaCola, entradaPartidaES))

        archEs.close()

        Estandar_mutex.release()
        Estandar_full.release()


        if (len(PartidaEstandar) == 15):
            #print("Partida estandar llena")
            time.sleep(7)
            Estandar()
        LockEstandar.release()

        #print("Partida Estandar: ", PartidaEstandar)
        
        #print("Cola estandar: ", ColaEstandar)

    elif cola == 1: #Partida Versus
        while(len(ColaVersus) == MAXVersus):
            if num not in EsperaVersus:
                EsperaVersus.append(num)
            CVVersus.wait()
            
        #print("----EsperaVersus----", EsperaVersus)

        primeroV = False
        if(len(EsperaVersus) > 0):
            if(EsperaVersus[0] == num):
                primeroV = True
            #print(".......primeroV......: ", primeroV)
            
            while(len(ColaVersus) == MAXVersus or not primeroV):
                CVVersus.wait()
                if(EsperaVersus[0] == num):
                    primeroV = True

        ColaVersus.append(num)

        if(len(EsperaVersus) > 0):
            EsperaVersus.pop(0)

        entradaCola = datetime.now()
        entradaCola = entradaCola.strftime("%H:%M:%S.%f")

        arch = open("Lobby.txt", "a")
        #s = "Jugador{0}, {1}, Partida Versus, {2}\n"

        arch.write("Jugador{0}, {1}, Partida Versus, {2}\n".format(num, entradaLobby, entradaCola))

        arch.close()

        LockLobby.release()
        
        Versus_empty.acquire()
        Versus_mutex.acquire()

        LockVersus.acquire()

        ColaVersus.pop(0)
        PartidaVersus.append(num)

        entradaPartidaV = datetime.now()
        entradaPartidaV = entradaPartidaV.strftime("%H:%M:%S.%f")

        archV = open("PartidaVersus.txt", "a")
        #sV = "Jugador{0}, {1}, {2}\n"
        archV.write("Jugador{0}, {1}, {2}\n".format(num, entradaCola, entradaPartidaV))

        archV.close()

        Versus_mutex.release()
        Versus_full.release()

        #print("Cola Versus: ", ColaVersus)

        if(len(PartidaVersus) == 2):
            #print("Partida Versus llena")
            time.sleep(3)
            Versus()

        LockVersus.release()

        #print("Partida Versus: ", PartidaVersus)

        

    elif cola == 2: #Partida Rápida
        while(len(ColaRapida) == MAXRapida):
            if(num not in EsperaRapida):
                EsperaRapida.append(num)
            CVRapida.wait()

        primeroRa = False
        if(len(EsperaRapida) > 0):
            if(EsperaRapida[0] == num):
                primeroRa = True
            #print(".......PRIMERO......: ", primeroRa)
            
            while(len(ColaRapida) == MAXRapida or not primeroRa):
                CVRapida.wait()
                if(EsperaRapida[0] == num):
                    primeroRa = True

        ColaRapida.append(num)

        entradaCola = datetime.now()
        entradaCola = entradaCola.strftime("%H:%M:%S.%f")

        arch = open("Lobby.txt", "a")
        #s = "Jugador{0}, {1}, Partida Rapida, {2}\n"

        arch.write("Jugador{0}, {1}, Partida Rapida, {2}\n".format(num, entradaLobby, entradaCola))

        arch.close()

        LockLobby.release()

        Rapida_empty.acquire()
        Rapida_mutex.acquire()

        LockRapida.acquire()

        ColaRapida.pop(0)
        PartidaRapida.append(num)

        entradaPartidaRa = datetime.now()
        entradaPartidaRa = entradaPartidaRa.strftime("%H:%M:%S.%f")

        archRa = open("PartidaRapida.txt", "a")
        #sRa = "Jugador{0}, {1}, {2}\n"
        archRa.write("Jugador{0}, {1}, {2}\n".format(num, entradaCola, entradaPartidaRa))

        archRa.close()        

        Rapida_mutex.release()
        Rapida_full.release()

        if(len(PartidaRapida) == 10):
            #print("Partida Rapida llena")
            time.sleep(6)
            Rapida()

        #print("Partida Rapida: ", PartidaRapida)

        #print("Cola Rapida: ", ColaRapida)

        LockRapida.release()

    elif cola == 3: #Partida Especial Navidad
        while(len(ColaNavidad) == MAXNavidad):
            if( num not in EsperaNavidad):
                EsperaNavidad.append(num)
            CVNavidad.wait()
        
        primeroNa = False
        if(len(EsperaNavidad) > 0):
            if(EsperaNavidad[0] == num):
                primeroNa = True
            #print(".......PRIMERO......: ", primeroNa)
            
            while(len(ColaNavidad) == MAXNavidad or not primeroNa):
                CVNavidad.wait()
                if(EsperaNavidad[0] == num):
                    primeroNa = True

        ColaNavidad.append(num)

        entradaCola = datetime.now()
        entradaCola = entradaCola.strftime("%H:%M:%S.%f")

        arch = open("Lobby.txt", "a")
        #s = "Jugador{0}, {1}, Partida Especial Navidad, {2}\n"

        arch.write("Jugador{0}, {1}, Partida Especial Navidad, {2}\n".format(num, entradaLobby, entradaCola))

        arch.close()

        LockLobby.release()

        Navidad_empty.acquire()
        Navidad_mutex.acquire()

        LockNavidad.acquire()

        ColaNavidad.pop(0)
        PartidaNavidad.append(num)

        entradaPartidaN = datetime.now()
        entradaPartidaN = entradaPartidaN.strftime("%H:%M:%S.%f")

        archN = open("PartidaEspecialNavidad.txt", "a")
        #sN = "Jugador{0}, {1}, {2}\n"
        archN.write("Jugador{0}, {1}, {2}\n".format(num, entradaCola, entradaPartidaN))

        archN.close()

        Navidad_mutex.release()
        Navidad_full.release()

        if(len(PartidaNavidad) == 12):
            #print("Partida Especial Navidad llena")
            time.sleep(5)
            Navidad()

        #print("Partida Especial Navidad: ", PartidaNavidad)

        #print("Cola Navidad: ", ColaNavidad)

        LockNavidad.release()

files=["Lobby.txt","PartidaEstandar.txt","PartidaVersus.txt","PartidaRapida.txt","PartidaEspecialNavidad.txt","Salida.txt"]
for f in files:
    if os.path.exists(f):
        os.remove(f)
    else:
        print(f'Archivo {f} no existe. Creando...\n')

entradaLobby = []
entradaCola = []

for i in range(1, 121):
    cola = random.randint(0,3)
    thread = threading.Thread(target=lobby, args=(cola, i))
    thread.start()

time.sleep(30)

if(len(PartidaEstandar) > 0 ):
    Estandar()
if(len(PartidaVersus) > 0):
    Versus()
if(len(PartidaRapida) > 0):
    Rapida()
if(len(PartidaNavidad) > 0):
    Navidad()
print("Apretar ctrl + c")
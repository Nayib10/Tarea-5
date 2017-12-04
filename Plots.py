import numpy as np
import matplotlib.pyplot as plt

datos = np.genfromtxt("RadialVelocities.dat", skip_header=1, delimiter=' ')
d = np.genfromtxt("dato.dat")
bayf = np.genfromtxt("bayfit.dat")

print "Masa Bulbo = %f , Masa Disco = %f , Masa Halo = %f" % (bayf[0]**2, bayf[1]**2, bayf[2]**2)

real = np.floor((bayf**2)*10000)*0.0001

plt.scatter(datos[:,0],datos[:,1], label = "Velocidades radiales medidas", color = 'm')
plt.plot(d[:,0],d[:,1], color = 'g')
plt.xlabel("Distancia al centro de la Galaxia (kpc)")
plt.ylabel("Velocidad Radial (km/s) ")
plt.suptitle("Datos y modelo: Velocidad radial vs radio")
subtitulo = "Masas: Bulbo = %f, Disco = %f, Halo = %f" % (real[0], real[1], real[2])
plt.title(subtitulo)
plt.savefig("plot.png")


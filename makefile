CC = cc -std=c11
MPICC = mpicc -std=c11
LIBS = -lgd
FLAGS = -I/opt/local/include -L/opt/local/lib



runRayTracer: traincar
	./traincar.exec

raytracer:
	$(CC) -o RayTracer.exec raytracer.c bitmapSaver 


valgrindTraincarVerbose: traincarDebug
	valgrind --leak-check=full --show-leak-kinds=all ./traincar.debug 
valgrindTraincar: traincarDebug
	valgrind --leak-check=yes --track-origins=yes ./traincar.debug 
	
traincarDebug:
	$(CC) -g -o traincar.debug traincar.c 
	
clean:
	rm -rf *.exec *.tmp *.debug
public class Multithreading extends Thread {
    private int largo_actual;
    private int largo_final;
    private int [][] matriz;
    private int coor_x;
    private int coor_y;
    private long startTime;
    private int coor_inicial_X;
    private int coor_inicial_y;

    public Multithreading(int largo_actual, int largo_final, int [][] matriz, int coor_x, int coor_y, long startTime) {
        this.largo_actual = largo_actual;
        this.largo_final = largo_final;
        this.matriz = matriz;
        this.coor_x = coor_x;
        this.coor_y = coor_y;
        this.startTime = startTime;
    }
    @Override
    public void run(){

        if (largo_actual == largo_final){

            boolean flag = false;
            int fila = 0, columna = 0;
            for(int i = coor_x; i<coor_x+largo_final; i++){
                for(int j = coor_y; j<coor_y+largo_final; j++){
                    if(matriz[i][j] == 1){
                        if(flag == false){
                            fila = i+1;
                            columna = j+1;
                            flag = true;
                            System.out.println("fila "+ fila + ", columna "+ columna);
                            long endTime = System.nanoTime();
                            double tiempo = (double) ((endTime-startTime));
                            System.out.println("Tiempo Hebras: "+tiempo +" nanosegundos");

                        }
                    }
                }
            }
            
            
        }
        else{
            Multithreading threads[] = new Multithreading[4];
            coor_inicial_X =coor_x;
            coor_inicial_y = coor_y;
            for(int i = 0; i<4;i++){
                coor_x = coor_inicial_X;
                coor_y = coor_inicial_y;
                switch (i) {
                    
                    case 0:
                        //do nothing 
                        break;

                    case 1:
                        coor_x += largo_actual/2;
                        break;

                    case 2:
                        coor_y += largo_actual/2;
                        
                        break;

                    case 3:

                    coor_x += largo_actual/2;
                    coor_y += largo_actual/2;
                    
                    break;
                }
                
                threads[i] = new Multithreading(largo_actual/2, largo_final, matriz, coor_x, coor_y, startTime);
                threads[i].start();
            }

            

            
        }
    }
}

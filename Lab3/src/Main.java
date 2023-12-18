import java.io.*;

public class Main{

    static int tamano_matriz, tamano_barco, matriz[][];
    static boolean THREADS = false;
    static boolean UNGABUNGA = false;
    public static void main(String args[])throws IOException {

        String DN = System.getProperty("user.dir");

        File archivo = null;
        FileReader fr = null;
        BufferedReader br = null;
        
        try {
            archivo = new File (DN+"/informe-nautico.txt");
            fr = new FileReader(archivo);
            br = new BufferedReader(fr);
            
            tamano_matriz = Integer.valueOf(br.readLine());
            tamano_barco = Integer.valueOf(br.readLine());

            String linea = br.readLine();
            String [] linea2 = linea.split(",");

            String linea_temp;

            matriz = new int[tamano_matriz][tamano_matriz];
            
            for(int i = 0; i<tamano_matriz; i++){
                linea_temp = linea2[i].replaceAll("[^0-9]+", "");
                for(int j = 0; j<tamano_matriz; j++){
                    if(linea_temp.charAt(j) == '1'){
                        matriz[i][j] += 1;
                    }
                }
            }
            
        } catch (Exception e) {
            e.printStackTrace();
        }finally{
            try {
                if (null != fr){
                    fr.close();
                }
            } catch (Exception e2) {
                e2.printStackTrace();
            }
        }

            long startTime1 = System.nanoTime();
            
            Multithreading thread = new Multithreading(tamano_matriz, tamano_barco, matriz, 0, 0, startTime1);
            
            thread.start();

            long startTime2 = System.nanoTime();
            boolean flag = false;
            int fila = 0, columna = 0;
            for(int i = 0; i<tamano_matriz; i++){
                for(int j = 0; j<tamano_matriz; j++){
                    if(matriz[i][j] == 1 && flag == false){
                        fila = i+1;
                        columna = j+1;
                        flag = true;
                        System.out.println("fila "+ fila + ", columna "+ columna);
                    }
                }
            }

            long endTime = System.nanoTime();
            double tiempo = (double) ((endTime-startTime2));
            System.out.println( "Tiempo busqueda lineal: "+ tiempo  +" nanosegundos");

    }
}
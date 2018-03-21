/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ponctuation;
import java.io.*;

/**
 *
 * @author zak
 */
public class Ponctuation {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        text("fichiertexte.txt");
       //dicos("a");
    }
    public static void dicos(String lettre){
        String chaine="";
        String chaine1="";
        String chaine2="";
	String fichier =lettre+"4-6.txt";
	String fichier1 =lettre+"7-10.txt";
	String fichier2 =lettre+"10-.txt";
	
	//lecture du fichier texte	
	try{
            
		BufferedReader br = new BufferedReader(new InputStreamReader (new FileInputStream(fichier),"ISO-8859-1")); 
		BufferedReader br1 = new BufferedReader(new InputStreamReader (new FileInputStream(fichier1),"ISO-8859-1")); 
		BufferedReader br2 = new BufferedReader(new InputStreamReader (new FileInputStream(fichier2),"ISO-8859-1")); 
		String ligne;
		String ligne1;
		String ligne2;
		while ((ligne=br.readLine())!=null){
			//System.out.println(ligne);
			chaine+=ligne+"\n";
		}
		br.close(); 
		while ((ligne1=br1.readLine())!=null){
			//System.out.println(ligne);
			chaine1+=ligne1+"\n";
		}
		br1.close(); 
		while ((ligne2=br2.readLine())!=null){
			//System.out.println(ligne);
			chaine2+=ligne2+"\n";
		}
		br2.close(); 
	}		
	catch (Exception e){
		System.out.println(e.toString());
	}
		//création ou ajout dans le fichier texte
	try {
		FileWriter fw = new FileWriter (fichier);
		BufferedWriter bw = new BufferedWriter (fw);
		PrintWriter fichierSortie = new PrintWriter (bw);
                chaine=chaine.replaceAll("é|è|ê|ë","e");
                chaine=chaine.replaceAll("à|ä|â","a");
                chaine=chaine.replaceAll("ù|ü|û","u");
                chaine=chaine.replaceAll("î|ï","i");
                chaine=chaine.replaceAll("ö|ô","i");
                chaine=chaine.replaceAll("ç","c");
                chaine=chaine.replaceAll("-|'"," ");
		fichierSortie.println (chaine); 
                //.replaceAll("[\\W]|_|[0-9]"," ")
		fichierSortie.close();
		FileWriter fw1 = new FileWriter (fichier1);
		BufferedWriter bw1 = new BufferedWriter (fw1);
		PrintWriter fichierSortie1 = new PrintWriter (bw1);
                chaine1=chaine1.replaceAll("é|è|ê|ë","e");
                chaine1=chaine1.replaceAll("à|ä|â","a");
                chaine1=chaine1.replaceAll("ù|ü|û","u");
                chaine1=chaine1.replaceAll("î|ï","i");
                chaine1=chaine1.replaceAll("ö|ô","i");
                chaine1=chaine1.replaceAll("ç","c");
                chaine1=chaine1.replaceAll("-|'"," ");
		fichierSortie1.println (chaine1); 
                //.replaceAll("[\\W]|_|[0-9]"," ")
		fichierSortie1.close();
		FileWriter fw2 = new FileWriter (fichier2);
		BufferedWriter bw2 = new BufferedWriter (fw2);
		PrintWriter fichierSortie2 = new PrintWriter (bw2);
                chaine2=chaine2.replaceAll("é|è|ê|ë","e");
                chaine2=chaine2.replaceAll("à|ä|â","a");
                chaine2=chaine2.replaceAll("ù|ü|û","u");
                chaine2=chaine2.replaceAll("î|ï","i");
                chaine2=chaine2.replaceAll("ö|ô","i");
                chaine2=chaine2.replaceAll("ç","c");
                chaine2=chaine2.replaceAll("-|'"," ");
		fichierSortie2.println (chaine2); 
                //.replaceAll("[\\W]|_|[0-9]"," ")
		fichierSortie2.close();
		System.out.println("Les fichiers " + fichier + " " + fichier1 + " " +  fichier2 +" ont été modifié!"); 
	}
	catch (Exception e){
		System.out.println(e.toString());
	}	
    }
    public static void text(String fichier){
        String chaine="";
	
	//lecture du fichier texte	
	try{
            
		BufferedReader br = new BufferedReader(new InputStreamReader (new FileInputStream(fichier),"ISO-8859-1")); 
		String ligne;
		while ((ligne=br.readLine())!=null){
			//System.out.println(ligne);
			chaine+=ligne+"\n";
		}
		br.close(); 
	}		
	catch (Exception e){
		System.out.println(e.toString());
	}
		//modification dans le fichier texte
	try {
		FileWriter fw = new FileWriter (fichier);
		BufferedWriter bw = new BufferedWriter (fw);
		PrintWriter fichierSortie = new PrintWriter (bw);
                chaine=chaine.replaceAll("é|è|ê|ë","e");
                chaine=chaine.replaceAll("à|ä|â","a");
                chaine=chaine.replaceAll("ù|ü|û","u");
                chaine=chaine.replaceAll("î|ï","i");
                chaine=chaine.replaceAll("ö|ô","i");
                chaine=chaine.replaceAll("ç","c");
                chaine=chaine.replaceAll("-|'"," ");
		fichierSortie.println (chaine/*.replaceAll("[\\W]|[0-9]"," ")*/); 
                //
		fichierSortie.close();
		
		System.out.println("Le fichier " + fichier + " a été modifié!"); 
	}
	catch (Exception e){
		System.out.println(e.toString());
	}		
    
    }
}

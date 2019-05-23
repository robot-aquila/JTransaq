package ru.prolib.JTransaq;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class JTransaqLoader {
	static final String RES_BIN = "/bin/win/x64";
	static final String LOC_BIN = "bin/win/x64";
	static final String DLL_EXT = ".dll";
	static final String JTRANSAQ64 = "JTransaq64";
	static final String TXMLCONNECTOR64 = "txmlconnector64";

	static void loadLibrary() {
		String arch = System.getProperty("os.arch");
		if ( "x86".equals(arch) ) {
			System.err.println("JTransaq supports x64 architecture only");
			System.exit(1);
		}
		try {
			extractLibrary(TXMLCONNECTOR64);
			extractAndLoadLibrary(JTRANSAQ64);
		} catch ( IOException e ) {
			System.err.println("Cannot extract library binaries: " + e.getMessage());
			System.exit(1);
		} catch ( UnsatisfiedLinkError e ) {
			System.err.println("Native code library failed to load: " + e.getMessage());
			System.exit(1);
		}
	}
	
	static void extractAndLoadLibrary(String lib_name) throws IOException, UnsatisfiedLinkError {
		System.load(extractLibrary(lib_name).getAbsolutePath());
	}
	
	static File extractLibrary(String lib_name) throws IOException {
		File dst_file = getLibraryFileL(lib_name);
		if ( dst_file.exists() ) {
			return dst_file;
		}
		
		String src_file = getLibraryFileR(lib_name);
		InputStream is = JTransaqLoader.class.getResourceAsStream(src_file);
		if ( is == null ) {
			throw new IOException("No library file in internal resources: " + src_file);
		}
		try ( OutputStream os = new FileOutputStream(dst_file) ) {
			copyStream(is, os);
		} finally {
			is.close();
		}
		return dst_file;
	}
	
	static void copyStream(InputStream is, OutputStream os) throws IOException {
		byte[] buffer = new byte[1024];
		int length;
		while ( (length = is.read(buffer)) > 0 ) {
			os.write(buffer, 0, length);
		}
	}
	
	static File getBinDirL() throws IOException {
		File dst = new File(LOC_BIN);
		if ( ! dst.exists() ) {
			if ( ! dst.mkdirs() ) {
				throw new IOException("Error creating directory: " + dst);
			}
		}
		return dst;
	}
	
	static File getBinFileL(String filename) throws IOException {
		return new File(getBinDirL(), filename);
	}
	
	static File getLibraryFileL(String lib_name) throws IOException {
		return getBinFileL(lib_name + DLL_EXT);
	}
	
	static String getBinDirR() {
		return RES_BIN;
	}
	
	static String getBinFileR(String filename) {
		return getBinDirR() + "/" + filename;
	}
	
	static String getLibraryFileR(String lib_name) {
		return getBinFileR(lib_name + DLL_EXT);
	}

}

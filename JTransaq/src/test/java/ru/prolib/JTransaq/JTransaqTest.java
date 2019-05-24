package ru.prolib.JTransaq;

import static org.junit.Assert.*;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Comparator;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class JTransaqTest {
	private File LOG_DIR;

	@Before
	public void setUp() throws Exception {
		LOG_DIR = Files.createTempDirectory("jtransaq-test-" + System.currentTimeMillis()).toFile();
		LOG_DIR.mkdirs();
	}
	
	@After
	public void tearDown() throws Exception {
		Files.walk(LOG_DIR.toPath())
	    	.sorted(Comparator.reverseOrder())
	    	.map(Path::toFile)
	    	.forEach(File::delete);
		LOG_DIR.delete();
	}

	@Test
	public void test() {
		JTransaqHandler handler = new JTransaqHandler() {
			
			@Override
			public boolean Handle(String data) {
				System.out.println("IN> " + data);
				return true;
			}

		};
		JTransaqServer server = new JTransaqServer(handler);
		//System.out.println("LOG_DIR=" + LOG_DIR);
		server.Initialize(LOG_DIR.getAbsolutePath(), 2);
		server.UnInitialize();
	}

}

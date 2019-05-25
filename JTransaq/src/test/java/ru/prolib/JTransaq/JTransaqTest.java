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
		deleteDir(new File("bin"));
		LOG_DIR = Files.createTempDirectory("jtransaq-test-" + System.currentTimeMillis()).toFile();
		LOG_DIR.mkdirs();
	}
	
	@After
	public void tearDown() throws Exception {
		deleteDir(LOG_DIR);
	}
	
	static void deleteDir(File path) throws Exception {
		if ( ! path.exists() ) {
			System.out.println("Nothing to do with directory: " + path.getAbsolutePath());
			return;
		}
		Files.walk(path.toPath())
    		.sorted(Comparator.reverseOrder())
    		.map(Path::toFile)
    		.forEach(File::delete);
		path.delete();
		System.out.println("Directory cleared: " + path.getAbsolutePath());
	}
	
	static class XHandler extends JTransaqHandler {
		@Override
		public boolean Handle(String data) {
			System.out.println("IN> " + data);
			return true;
		}
	}

	@Test
	public void test1() throws Exception {
		XHandler handler = new XHandler();
		JTransaqServer server = new JTransaqServer(handler);
		//System.out.println("LOG_DIR=" + LOG_DIR);
		server.Initialize(LOG_DIR.getAbsolutePath(), 2);
		server.UnInitialize();
	}
	
	@Test
	public void test2() throws Exception {
		XHandler handler = new XHandler();
		JTransaqServer server = new JTransaqServer(handler);
		try {
			server.Initialize("zulu\\charlie", 2);
			fail("Expected exception: " + Exception.class.getSimpleName());
		} catch ( Exception e ) {
			String expected = new StringBuilder()
					.append("<error>")
					.append("Не удалось инициализировать библиотеку. ")
					.append("Указанный путь не существует")
					.append("</error>")
					.toString();
			assertEquals(expected, e.getMessage());
		}
	}

}

package ru.prolib.JTransaq;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class JTransaqTest {

	@Before
	public void setUp() throws Exception {
		
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
		System.out.println("init: " + server.Initialize("foo/bar", 1));
		server.UnInitialize();
	}

}

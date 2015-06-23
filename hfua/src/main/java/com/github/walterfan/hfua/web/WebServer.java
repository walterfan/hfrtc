package com.github.walterfan.hfua.web;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.math.NumberUtils;

import org.eclipse.jetty.server.Handler;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.DefaultHandler;
import org.eclipse.jetty.server.handler.HandlerList;
import org.eclipse.jetty.server.handler.ResourceHandler;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.eclipse.jetty.util.log.Log;
import org.eclipse.jetty.util.log.Logger;
import org.jboss.resteasy.plugins.server.servlet.HttpServletDispatcher;

import com.github.walterfan.service.IService;
import com.github.walterfan.util.ConfigLoader;

public class WebServer extends HttpServlet implements IService {
	
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private static final Logger logger = Log.getLogger(WebServer.class);
	private static final String CONFIG_DIR = "./etc";
	private static final String CMD_PATH = "/cmd/v1/*";
	private static final String API_PATH = "/api/v1/*";
	private static String CONFIG_FILE = "hfrtc.properties";
	private static int WEB_PORT = 8080;
	private static String HOME_PAGE = "index.html";
	private static String HOME_FOLDER = "./site";
	
	private int webPort = WEB_PORT;
	private Server _server;
	private WebHandler webHandler;

	
	
	public int getWebPort() {
		return webPort;
	}

	public void setWebPort(int webPort) {
		this.webPort = webPort;
	}

	public void init() {
		ConfigLoader cfgLoader = ConfigLoader.getInstance();
		try {
			cfgLoader.loadFromClassPath(CONFIG_FILE);
		} catch (IOException e) {
			e.printStackTrace();
		}

		HOME_PAGE = cfgLoader.getProperty("HOME_PAGE","index.html");
		HOME_FOLDER = cfgLoader.getProperty("HOME_FOLDER","./site");
		WEB_PORT = NumberUtils.toInt(cfgLoader.getProperty("WEB_PORT","" + WEB_PORT));
		
		WebHandler webHandler = new WebCmdHandler();
		this.setWebHandler(webHandler);
		
		
	}
	
	public WebHandler getWebHandler() {
		return webHandler;
	}



	public void setWebHandler(WebHandler webHandler) {
		this.webHandler = webHandler;
	}



	

	public Handler createStaticWebApp(String homeFolder, String homePage) throws Exception {

		ResourceHandler resource_handler = new ResourceHandler();

		resource_handler.setDirectoriesListed(true);
		resource_handler.setWelcomeFiles(new String[] { homePage });
		resource_handler.setResourceBase(homeFolder);

		return resource_handler;

	}

	public Handler createServletApp(String path) throws Exception {

        
        ServletHandler handler = new ServletHandler();
		handler.addServletWithMapping(WebServer.class, path);
			
		return handler;
	}

    public Handler createRestfulApp(String path) {
    	ServletContextHandler context = new ServletContextHandler(
				ServletContextHandler.SESSIONS);
		context.setContextPath("/");
		ServletHolder servletHolder = new ServletHolder(
				new HttpServletDispatcher());
		servletHolder.setInitParameter("javax.ws.rs.Application",
				"com.github.walter.rest.RestfulApplication");
		context.addServlet(servletHolder, path);
		return context;
    }
	
	@Override
	protected void doGet(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		doPost(request, response);
	}
	
	@Override
	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		logger.info("waltertest: " + webHandler);
		if(null != webHandler) {
			this.webHandler.handle(request, response);
			return;
		} 
			
		response.setContentType("text/html");
		response.setStatus(HttpServletResponse.SC_OK);
		response.getWriter().println("<h3>Sorry, the handler have not be implemented</h3>" + request.getServletPath());
		
	}
	
	
	


	@Override
	public void start() throws Exception {
		
		
		_server = new Server(this.webPort);
		
		HandlerList handlers = new HandlerList();

		Handler handler2 = createStaticWebApp(HOME_FOLDER, HOME_PAGE);
		Handler handler3 = createServletApp(CMD_PATH);
		Handler handler4 = createRestfulApp(API_PATH);
		Handler handler5 = new DefaultHandler();
		
		
		handlers.addHandler(handler2);
		handlers.addHandler(handler3);
		handlers.addHandler(handler4);
		handlers.addHandler(handler5);
		
		_server.setHandler(handlers);
		_server.start();
		//_server.join();
	}

	@Override
	public void stop() throws Exception {
		_server.stop();
		_server.join();
		
	}

	@Override
	public boolean isStarted() {
		if(null == this._server)
			return false;
		return this._server.isStarted();		
	}

	@Override
	public void clean() throws Exception {
		this._server.destroy();
		
	}

	@Override
	public String getName() {
		return "WebApplication";
	}

	
	public static void main(String[] args) throws Exception {

		int nPort = args.length == 0 ? WEB_PORT : Integer.parseInt(args[0]);
		
		WebServer webApp = new WebServer();
		webApp.setWebPort(nPort);
		webApp.init();
		webApp.start();

		
		
	}
}

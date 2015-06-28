package com.github.walterfan.hfua.web;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;




import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.math.NumberUtils;
import org.eclipse.jetty.server.Handler;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.eclipse.jetty.server.handler.ContextHandler;
import org.eclipse.jetty.server.handler.DefaultHandler;
import org.eclipse.jetty.server.handler.ErrorHandler;
import org.eclipse.jetty.server.handler.HandlerList;
import org.eclipse.jetty.server.handler.ResourceHandler;
import org.eclipse.jetty.servlet.DefaultServlet;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.eclipse.jetty.util.log.Log;
import org.eclipse.jetty.util.log.Logger;
import org.jboss.resteasy.plugins.server.servlet.HttpServletDispatcher;









import com.github.walterfan.devaid.http.JettyHandlerAdapter;
import com.github.walterfan.devaid.http.WebHandler;
import com.github.walterfan.service.IService;
import com.github.walterfan.util.ConfigLoader;


public class WebServer extends HttpServlet implements IService {
	
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private static final Logger logger = Log.getLogger(WebServer.class);
	private static final String CONFIG_DIR = "./etc";
	
	private static final String API_PATH = "/api/v1/*";
	private static String CONFIG_FILE = "hfrtc.properties";
	private static int WEB_PORT = 8080;
	private static String HOME_PAGE = "index.html";
	private static String HOME_FOLDER = "./site";
	
	private int webPort = WEB_PORT;
	private Server _server;
	//private WebHandler webHandler;
	private Map<String, WebHandler> webHandlers = new HashMap<String, WebHandler>();
	
	
	public Map<String, WebHandler> getWebHandlers() {
		return webHandlers;
	}

	public void setWebHandlers(Map<String, WebHandler> webHandlers) {
		this.webHandlers = webHandlers;
	}

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
		
		//WebHandler webHandler = new WebCmdHandler();
		//this.setWebHandler(webHandler);
		
		
	}
	
	



	

	public Handler createStaticWebApp(String homeFolder, String homePage) throws Exception {

		ResourceHandler resource_handler = new ResourceHandler();

		resource_handler.setDirectoriesListed(true);
		resource_handler.setWelcomeFiles(new String[] { homePage });
		resource_handler.setResourceBase(homeFolder);

		return resource_handler;

	}
	
	public Handler createServletHandler(String path, Handler handler) {

        
        ContextHandler context1 = new ContextHandler();
        context1.setContextPath(path);
        context1.setResourceBase(".");
        context1.setClassLoader(Thread.currentThread().getContextClassLoader());
        context1.setHandler(handler);

        return context1;
	}

	public void addWebHandlers(Server svr, HandlerList handlers) throws Exception {

        for(Map.Entry<String, WebHandler> entry: webHandlers.entrySet()) {
        	String path = entry.getKey();
        	WebHandler webHandler = entry.getValue();
        	if(null == webHandler) {
        		continue;
        	}
        	
        	Handler jettyHandler = new JettyHandlerAdapter(webHandler);
        	
        	ContextHandler ctxHandler = new ContextHandler();
        	
        	ctxHandler.setContextPath(path);
        	ctxHandler.setHandler(jettyHandler);
        	ctxHandler.setAllowNullPathInfo(true);
        	
        	handlers.addHandler(ctxHandler);
            
        	logger.info(path + " is set with handler: " + jettyHandler);
        }
       

	}

    public Handler createRestfulApp(String path) {
    	ServletContextHandler context = new ServletContextHandler(
				ServletContextHandler.SESSIONS);
		context.setContextPath("/");
		ServletHolder servletHolder = new ServletHolder(
				new HttpServletDispatcher());
		servletHolder.setInitParameter("javax.ws.rs.Application",
				"com.github.walterfan.hfua.rest.RestfulApplication");
		context.addServlet(servletHolder, path);
		return context;
    }
	
	/*@Override
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
	*/
	
	


	@Override
	public void start() throws Exception {
		
		
		_server = new Server(this.webPort);
		
		HandlerList handlers = new HandlerList();

		Handler staticWebHandler = createStaticWebApp(HOME_FOLDER, HOME_PAGE);
		Handler restWebHandler = createRestfulApp(API_PATH);
		//Handler defaultHandler = new DefaultHandler();
		//Handler testHandler = createServletHandler("/test");
		
		handlers.addHandler(staticWebHandler);
		handlers.addHandler(restWebHandler);
		//handlers.addHandler(defaultHandler);
		//handlers.addHandler(testHandler);

		addWebHandlers(_server, handlers);
		
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

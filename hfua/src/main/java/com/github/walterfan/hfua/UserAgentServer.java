package com.github.walterfan.hfua;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.github.walterfan.service.AbstractService;
import com.github.walterfan.service.ServiceMgr;
import com.github.walterfan.service.GlobalBeanFactory;

public class UserAgentServer extends AbstractService {

	private static Log logger = LogFactory.getLog(UserAgentServer.class);
	
	private GlobalBeanFactory beanFactory;
	private ServiceMgr serviceMgr;
	
	@Override
	protected void onStart() throws Exception {
		if(null != serviceMgr) 
			serviceMgr.start();
		
	}

	@Override
	protected void onStop() throws Exception {
		if(null != serviceMgr) 
			serviceMgr.stop();

		
	}

	@Override
	public String getName() {
		return "UserAgent";
	}

	@Override
	protected void onInit() throws Exception {
		String xmlFiles = "spring-config.xml";
		beanFactory = GlobalBeanFactory.getInstance(xmlFiles);
		serviceMgr = (ServiceMgr)beanFactory.getBean("serviceMgr");
		
		if(null != serviceMgr) 
			serviceMgr.init();
	}

	@Override
	protected void onClean() throws Exception {
		if(null != serviceMgr) 
			serviceMgr.clean();
		
	}

	public static void main(String[] args) {
		UserAgentServer ua = new UserAgentServer();
		try {
			ua.init();
			ua.start();
		} catch (Exception e) {
			e.printStackTrace();
			//logger.error(e);
			try {
				ua.stop();
				ua.clean();
			} catch (Exception e1) {
				e1.printStackTrace();
				//logger.error(e1);
			}
		}
		
		

	}
}

package com.github.walterfan.hfua.biz;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;



public class RoomService {


	private static Log logger = LogFactory.getLog(RoomService.class);

	public static void main(String[] args) {

		try {

			ApplicationContext ctx = new ClassPathXmlApplicationContext(
					"spring-config.xml");


			//LinkService service = (LinkService) ctx.getBean("linkService");

			logger.info("Running App...");

//			// ( 1 ) SELECT ALL PARENTS
//			System.out.println("( 1 ) selectAllLink()");
//			List<Link> parents = service.selectAllLink();
//			System.out.println("-> " + parents);
			
			
		} catch (Exception e) {
			logger.error("error: ", e);
		}
	}

}

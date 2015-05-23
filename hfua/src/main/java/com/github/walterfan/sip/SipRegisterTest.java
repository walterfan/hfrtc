package com.github.walterfan.sip;

import java.net.InetAddress;


public class SipRegisterTest {
	
	private static final String SIP_DOMAIN = "@walterfan.github.com";
	private static final String UAC_ADDR = "10.224.57.140:5060";
	private static final String UAS_ADDR = "2.2.8.240:5062";
	private static long accessCode = Long.parseLong(RandomUtils.getRandomNumbers(9));
	
	public void usage() {
		System.out.println("Usage: java -cp .. SipRegisterTest nlocalPort strRemoteHostPort strRegisterHostPort");
	}
	
	public static void testRegister200(String args[]) throws Exception {
		int nLocalPort = args.length == 0 ? 5062 : Integer.parseInt(args[0]);		
		String strLocalHost = InetAddress.getLocalHost().getHostAddress();
		String strRemoteHost = UAS_ADDR;
		if(args.length > 1) {
			strRemoteHost = args[1];
		}
		String strTasHost = UAC_ADDR;
		if(args.length > 2) {
			strTasHost = args[2];
		}
		
		SipUserAgent ua = new SipUserAgent(strLocalHost, nLocalPort);
		ua.setMessageProcessor(new SipMessageHandler());
		// user name, src addr, dest addr, domain
		
		String seq = ua.sendRegisterRequest("" + (accessCode++), strTasHost , strRemoteHost, "walterfan.github.com");
		ua.addExpection(seq, 200);
		
		ua.waitResult(5);
		int errCnt = ua.checkResult();
		System.out.println("failed case: " + errCnt);
	}
	
	public static void testUnRegister200(String args[]) throws Exception {
		
		int nLocalPort = args.length == 0 ? 5062 : Integer.parseInt(args[0]);
		
		String strLocalHost = InetAddress.getLocalHost().getHostAddress();
		String strRemoteHost = UAS_ADDR;
		if(args.length > 1) {
			strRemoteHost = args[1];
		}
		String strTasHost = UAC_ADDR;
		if(args.length > 2) {
			strTasHost = args[2];
		}
		SipUserAgent ua = new SipUserAgent(strLocalHost, nLocalPort);
		ua.setMessageProcessor(new SipMessageHandler());
		// user name, src addr, dest addr, domain
		
		SipRequestInfo sipReq = new SipRequestInfo();
		long meetingkey = accessCode++;
		sipReq.setRequestUri("sip:" + strRemoteHost);
		sipReq.setToUri("sip:" + meetingkey +SIP_DOMAIN);
		sipReq.setFromUri("sip:" + meetingkey +SIP_DOMAIN);
		sipReq.setContactUri("sip:" + strTasHost, "1", 180);
		sipReq.setUserAgent("TAS");
		sipReq.setExpireTime(0);
		
		String seq = ua.sendRequest(sipReq);		
		ua.addExpection(seq, 423);
		
		ua.waitResult(5);
		int errCnt = ua.checkResult();
		System.out.println("failed case: " + errCnt);
	}
	
	public static void testRegister423(String args[]) throws Exception {
		
		int nLocalPort = args.length == 0 ? 5062 : Integer.parseInt(args[0]);
		
		String strLocalHost = InetAddress.getLocalHost().getHostAddress();
		String strRemoteHost = UAS_ADDR;
		if(args.length > 1) {
			strRemoteHost = args[1];
		}
		SipUserAgent ua = new SipUserAgent(strLocalHost, nLocalPort);
		ua.setMessageProcessor(new SipMessageHandler());
		// user name, src addr, dest addr, domain
		
		SipRequestInfo sipReq = new SipRequestInfo();
		long meetingkey = accessCode++;
		sipReq.setRequestUri("sip:" + strRemoteHost);
		sipReq.setToUri("sip:" + meetingkey +SIP_DOMAIN);
		sipReq.setFromUri("sip:" + meetingkey +SIP_DOMAIN);
		sipReq.setContactUri("sip:" + strRemoteHost, "1", 180);
		sipReq.setUserAgent("TAS");
		String seq = ua.sendRequest(sipReq);		
		ua.addExpection(seq, 423);
		
		ua.waitResult(5);
		int errCnt = ua.checkResult();
		System.out.println("failed case: " + errCnt);
	}

	
	public static void main(String args[]) {

		
		try
        {
			testRegister200(args);
			testUnRegister200(args);
			testRegister423(args);
        } 
		catch (Throwable e)
        {
            System.out.println("Problem initializing the SIP stack.");
            e.printStackTrace();
            System.exit(-1);
        }

    }

	
}

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
   
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   /*System.out.println(urlVal.isValid("http://www.amazon.com")); //returns true -good
	   System.out.println(urlVal.isValid("http://goog>le.com/search"));  //returns false -good
	   System.out.println(urlVal.isValid("http:/amazon.com"));  //returns false -good
	   System.out.println(urlVal.isValid("://amazon.com"));  //returns false -good
	   System.out.println(urlVal.isValid("4htp://www.amazon.com")); //returns false -good
	   System.out.println(urlVal.isValid("http://amazon.com/.."));  //returns false -good
	   System.out.println(urlVal.isValid("http://amazon.com/$hey"));  //returns true -good
	   System.out.println(urlVal.isValid("http://amazon.com/here?/"));  //returns false -good
	   System.out.println(urlVal.isValid("http://www.amazon.com:-1")); //returns false -good
	   System.out.println(urlVal.isValid("http://www.amazon.com:80")); //returns true -good
	   System.out.println(urlVal.isValid("http://amazon.com/path//"));  //returns false -good
	   */
	   //can't find the bug here???
   }
   
   
   public void testYourFirstPartitionProgrammatic(ResultPair[] scheme)
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String authority = "www.amazon.com";
	   String url;
	   boolean result;
	   
	   for (int i=0; i < scheme.length; i++) {
		   url = scheme[i].item + authority;
		   result = urlVal.isValid(url);
		   if (result == scheme[i].valid){
			   System.out.printf("isValid passed for scheme.\n");
		   }
		   else {
			   System.out.printf("isValid failed for scheme %s. Expected: %s \t Received: %s \n", scheme[i].item, scheme[i].valid, result);
		   }
	   }
   }
	   
   
   public void testYourSecondPartitionProgrammatic(ResultPair[] authority)
   {
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String scheme = "http://";
	   String url;
	   boolean result;
	   
	   for (int i = 0; i < authority.length; i++) {
		   url = scheme + authority[i].item;
		   result = urlVal.isValid(url);
		   if (result == authority[i].valid) {
			   System.out.printf("isValid passed for authority. \n");
		   }
		   else {
			   System.out.printf("isValid failed for authority %s. Expected: %s \t Received: %s \n", authority[i].item, authority[i].valid, result);
		   }
	   }
	   
   }
   
   public void testYourThirdPartitionProgrammatic(ResultPair[] path){
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String base = "http://www.amazon.com";
	   String url;
	   boolean result;
	   
	   for (int i = 0; i < path.length; i++) {
		   url = base + path[i].item;
		   result = urlVal.isValid(url);
		   if (result == path[i].valid) {
			   System.out.printf("isValid passed for path. \n");
		   }
		   else {
			   System.out.printf("isValid failed for path %s. Expected: %s \t Received: %s \n", path[i].item, path[i].valid, result);
		   }
	   }
	   
   }
   
   
   public void testYourFourthPartitionProgrammatic(ResultPair[] port) {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String base = "http://www.amazon.com";
	   String url;
	   boolean result;
	   
	   for (int i = 0; i < port.length; i++) {
		   url = base + port[i].item;
		   result = urlVal.isValid(url);
		   if (result == port[i].valid) {
			   System.out.printf("isValid passed for port. \n");
		   }
		   else {
			   System.out.printf("isValid failed for port %s. Expected: %s \t Received: %s \n",port[i].item, port[i].valid, result);
		   }
	   }
   }
   
   
   public void testYourFifthPartitionProgrammatic(ResultPair[] query) {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String base = "http://www.amazon.com/path";
	   String url;
	   boolean result;
	   
	   for (int i = 0; i < query.length; i++) {
		   url = base + query[i].item;
		   result = urlVal.isValid(url);
		   if (result == query[i].valid) {
			   System.out.printf("isValid passed for query. \n");
		   }
		   else {
			   System.out.printf("isValid failed for query %s. Expected: %s \t Received: %s \n",query[i].item, query[i].valid, result);
		   }
	   }
   }
   
   
   public void testIsValid(ResultPair[][] testObjects, long options)
   {
	   UrlValidator urlVal = new UrlValidator(null, null, options);
	   String url;
	   boolean validity;
	   boolean result;
	   
	  //O(n^5)...should i write it differently??
	  //scheme
	  for (int i = 0; i < testObjects[0].length; i++) {
		  //authority
		  for (int j = 0; j < testObjects[1].length; j++) {
			  //port
			  for (int k = 0; k < testObjects[2].length; k++) {
				  //path
				  for (int m = 0; m < testObjects[3].length; m++) {
					  //query
					  for (int n = 0; n < testObjects[4].length; n++) {
						  validity = testObjects[0][i].valid && testObjects[1][j].valid && testObjects[2][k].valid && testObjects[3][m].valid && testObjects[4][n].valid;
						  url = testObjects[0][i].item + testObjects[1][j].item + testObjects[2][k].item + testObjects[3][m].item + testObjects[4][n].item;
						  result = urlVal.isValid(url);
						  if (validity != result) {
							  System.out.printf("Expected: %s \t Actual: %s \t url: %s \n", validity, result, url);
						  }
					  }
				  }
				  
			  }
		  }
	  }
	  
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */

   
   public static void main(String[] args) {
	
	   UrlValidatorTest tester = new UrlValidatorTest("test1");
	   
	   ResultPair[] scheme = {new ResultPair("http://", true),
			   					new ResultPair("https://", true),
			   					new ResultPair("5http://", false),
			   					new ResultPair("zhttp://", true),
			   					new ResultPair("Zhttp://", true),
			   					new ResultPair("0http://", false),
			   					new ResultPair("h+++ttp://", true),
			   					new ResultPair("h---ttp://", true),
			   					new ResultPair("h...ttp://", true),
			   					new ResultPair("h!!!ttp://", false),
			   					new ResultPair("h99ttp://", true),
			   					new ResultPair("", false)}; //should this be true??
	   
	   
	   ResultPair[] authority = {new ResultPair("www.amazon.com", true),
			   					new ResultPair("www.utk.edu", true),
			   					new ResultPair("www/utk/edu", false),
			   					new ResultPair("www.hello-world.com", true),
			   					new ResultPair("www-hello-world-com", false),
			   					new ResultPair("www.---.com", false),
			   					new ResultPair("www.--", false),
			   					new ResultPair(".hello", false),
			   					new ResultPair("docs.google.com", true),
			   					new ResultPair("www.80:1:30", false),
			   					new ResultPair("255.255.255.255", true),
			   					new ResultPair("1.1.1", false)};
	   
	   ResultPair[] path = {new ResultPair("/path", true),
			   				new ResultPair("/path22", true),
			   				new ResultPair("b.32", false),
			   				new ResultPair("", true),
			   				new ResultPair("//path", false),
			   				new ResultPair("/path/here", true),
			   				new ResultPair("/path/here#", true),
			   				new ResultPair("/9path", true),
			   				new ResultPair("/path//here", false),
			   				new ResultPair("/path \n /here", false),
			   				new ResultPair("/../", false),
			   				new ResultPair(":", false)};
	   
	   ResultPair[] port = {new ResultPair(":0", true),
			   				new ResultPair(":1", true),
			   				new ResultPair(":-1", false),
			   				new ResultPair(":-99999", false),
			   				new ResultPair(":1000", true),
			   				new ResultPair(":1025", true),
			   				new ResultPair(":999", true),
			   				new ResultPair(":99999", false),
			   				new ResultPair(":555", true),
			   				new ResultPair(":!$%", false),
			   				new ResultPair(":test", false)};
	   
	   ResultPair[] query = {new ResultPair("?query=hey", true),
			   				new ResultPair("?query=hey&what=up", true),
			   				new ResultPair("?q=1,2,3", true),
			   				new ResultPair("?q=1;2;3", true),
			   				new ResultPair(":::", false),
			   				new ResultPair("", true)
			   
	   };
	   
	   tester.testYourFirstPartitionProgrammatic(scheme);
	   tester.testYourSecondPartitionProgrammatic(authority);
	   tester.testYourThirdPartitionProgrammatic(path);
	   tester.testYourFourthPartitionProgrammatic(port);
	   tester.testYourFifthPartitionProgrammatic(query);
	   
	   ResultPair[][] testObjects = {scheme, authority, port, path, query};
	   long ALLOW_ALL_SCHEMES = 1 << 0;
	   //tester.testIsValid(testObjects, ALLOW_ALL_SCHEMES);
	   
   }
   
   
}



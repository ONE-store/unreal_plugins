# ONE store InApp v19 unreal plugins (Beta)

You can see the detail guide in the ONEstore developer center. <br>
[Please click here to a guide.](https://dev.onestore.co.kr/wiki/en/x/9wJZ)

## Supported Engine Version

- 4.25 


## OneStoreIap : Blue Prints for Unreal And android libraries


 ### One Store Iap Get Product Details
 It requests the details of in-app products registered on ONE store.<br>
 As for Managed product, call up the specification with “inapp” in the product type. As for Monthly auto-renewal product, call up the specification with “auto”.<br>
As for in-app calls, memory issues might happen, so it is recommended to search by 20 to 30 in-apps at a time.<br>
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833493/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.00.39.png)

 <br>
 
 ### One Store Iap Purchase Info
 The purchase history of non-consumed Managed product and Monthly auto-renewal product can be checked.<br>
 Check in-app products by specifying Managed product or Monthly auto-renewal product in the product type.<br>
 
  ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833490/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+3.59.37.png)
  
 <br>
 
 ### One Store Iap Consume Purchase 
 For consumable products that need to be re-purchased, you must proceed with ‘consume’ and item provision after successful purchase. <br>
 If these products are not processed as ‘consume’, they can never be purchased again.<br>
 For ONE store IAP SDK V19 and later, if ‘consume’ or ‘acknowledge’ is not made within 3 days, the purchase will be cancelled since it will be judged that items have not been provided.<br> 
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833495/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.21.29.png)
 
 <br>
 
 ### One Store Iap Acknowledge Purchase 
 It is a function to acknowledge the in-app which has been successfully purchased. When it comes to Managed product to be used as non-consumable product, or Monthly auto-renewal product, it must call up ‘acknowledge’. <br>
 For ONE store IAP SDK V19 and later, if ‘consume’ or ‘acknowledge’ is not made within 3 days, the purchase will be cancelled since it will be judged that items have not been provided.<br> 
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833494/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.29.24.png)
 
 <br>
 
 ### One Store Iap Request Purchase 
 It requests ONE store in-app purchases (IAP).<br> 
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833492/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.14.54.png)
 
 <br>
 
 ### One Store Iap Manage Requrring 
 It changes Monthly auto-renewal product status.<br>
 There are 2 types of status: cancel or reactive. As for ‘cacel’, automatic payment will not be made on the next payment date.<br> 
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833481/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.32.48.png)
 
 <br>
 
 ### One Store Iap Request Login
 It is used to process ONE store login when calling up On Need Login among the response types of the specifications above.<br>
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833483/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.40.27.png)
 
 <br>
 
 ### One Store Iap Request Update 
 It is used to process ONE update when calling up On Need Update among the response types of the specifications above. <br>
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833482/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.43.04.png)
 
 <br>
 
 ### One Store Iap Get Store Code 
 As for v19, it provides the API delivering market identification codes available in S2S API. <br> 
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833480/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.37.25.png)
 
 <br>
 
 ### One Store Purchse Verify 
 It reviews signature and purchase data through the license key (public key) issued by Developer Center with the API supporting the review of the purchase data.<br>
 However, as for the review of servers, it is recommended to review server items rather than to use this API. <br>
 
 ![enter image description here](https://dev.onestore.co.kr/wiki/en/doc/files/5833463/5833485/1/1607999424000/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA+2020-08-31+%E1%84%8B%E1%85%A9%E1%84%92%E1%85%AE+4.47.45.png)
 
 <br>
 


## AdapterSourceCode : Source codes of onestoreUnreal.jar  

Source code for the adapter library.
Download and build to make changes to the Unreal plugins.





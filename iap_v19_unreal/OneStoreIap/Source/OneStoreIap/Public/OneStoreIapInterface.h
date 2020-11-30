// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OneStoreIapInterface.generated.h"

#define RESULT_OK							0 // 성공
#define RESULT_USER_CANCELED				1 // 결제가 취소되었습니다
#define RESULT_SERVICE_UNAVAILABLE			2 // 단말 또는 서버 네트워크 오류가 발생하였습니다.
#define RESULT_BILLING_UNAVAILABLE			3 // 구매 처리 과정에서 오류가 발생하였습니다.
#define RESULT_ITEM_UNAVAILABLE				4 // 상품이 판매중이 아니거나 구매할 수 없는 상품입니다.
#define RESULT_DEVELOPER_ERROR				5 // 올바르지 않은 요청입니다.
#define RESULT_ERROR						6 // 정의되지 않은 기타 오류가 발생했습니다.
#define RESULT_ITEM_ALREADY_OWNED			7 // 이미 아이템을 소유하고 있습니다.
#define RESULT_ITEM_NOT_OWNED				8 // 아이템을 소유하고 있지 않아 소비할 수 없습니다.
#define RESULT_FAIL							9 // 결제에 실패했습니다. 결제 가능 여부 및 결제 수단을 확인 후 다시 결제해주세요.
#define RESULT_NEED_LOGIN					10 // 스토어 앱 로그인이 필요합니다.
#define RESULT_NEED_UPDATE					11 // 결제 모듈의 업데이트가 필요합니다.
#define RESULT_SECURITY_ERROR				12 // 비정상 앱에서 결제가 요청되었습니다.
#define RESULT_BLOCKED_APP					13 // 요청이 차단되었습니다
#define RESULT_NOT_SUPPORT_SANDBOX			14 // 테스트 환경에서는 지원하지 않는 기능입니다.
#define ERROR_DATA_PARSING					1001 // 응답 데이터 파싱 오류가 발생했습니다.
#define ERROR_SIGNATURE_VERIFICATION		1002 // 구매정보의 서명검증 에러가 발생했습니다.
#define ERROR_ILLEGAL_ARGUMENT				1003 // 정상적이지 않은 파라미터가 입력 되었습니다.
#define ERROR_UNDEFINED_CODE				1004 // 정의되지 않은 오류가 발생했습니다.
#define ERROR_SIGNATURE_NOT_VALIDATION		1005 // 입력한 라이센스 키가 유효하지 않습니다.
#define ERROR_UPDATE_OR_INSTALL				1006 // 결제 모듈 설치에 실패하였습니다.
#define ERROR_SERVICE_DISCONNECTED			1007 // 결제 모듈과의 연결이 끊어졌습니다.
#define ERROR_FEATURE_NOT_SUPPORTED			1008 // 기능을 지원하지 않습니다.
#define ERROR_SERVICE_TIMEOUT				1009 // 서비스와 통신하는 시간이 초과되었습니다.
#define RESULT_EMERGENCY_ERROR				99999 // 서버 점검중입니다.

#define ONESTORE_REQUEST					800 
#define ONESTORE_REQUEST_PRODUCT_DETAIL		ONESTORE_REQUEST + 1 // Get Product Request
#define ONESTORE_REQUEST_PURCHASE			ONESTORE_REQUEST + 2 // Get Purchase Request
#define ONESTORE_REQUEST_CONSUME			ONESTORE_REQUEST + 3 // Consume Purchase Request
#define ONESTORE_REQUEST_ACKNOWLEDGE		ONESTORE_REQUEST + 4 // Acknowledge Purchase Request
#define ONESTORE_REQUEST_MANAGED_RECURRING	ONESTORE_REQUEST + 5 // Managed Recurring Request
#define ONESTORE_REQUEST_STORECODE			ONESTORE_REQUEST + 6 // Get StoreCode Request
#define ONESTORE_REQUEST_LOGIN				ONESTORE_REQUEST + 7 // Request Login Request
#define ONESTORE_REQUEST_UPDATE				ONESTORE_REQUEST + 8 // Request Update Request

USTRUCT(BlueprintType)
struct FOneStoreIapProductData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = ProductData)
	FString OriginalProductJson;

	UPROPERTY(BlueprintReadOnly, Category = ProductData)
	FString ProductId;

	UPROPERTY(BlueprintReadOnly, Category = ProductData)
	FString Type;

	UPROPERTY(BlueprintReadOnly, Category = ProductData)
	FString Price;

	UPROPERTY(BlueprintReadOnly, Category = ProductData)
	FString PriceCurrencyCode;

	UPROPERTY(BlueprintReadOnly, Category = ProductData)
	FString PriceAmountMicros;

	UPROPERTY(BlueprintReadOnly, Category = ProductData)
	FString Title;

};

USTRUCT(BlueprintType)
struct FOneStoreIapPurchaseData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString OrderId;

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString PackageName;

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString ProductId;

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString PurchaseTime;

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString AcknowlegeState;

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString DeveloperPayload;

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString PurchaseId;

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString PurchaseToken;
	
	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString BillingKey;

	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString OriginalPurchaseData;

	// Opaque receipt data for the transaction
	UPROPERTY(BlueprintReadOnly, Category = PurchaseData)
	FString SignatureData;
};


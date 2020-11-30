// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OneStoreIapInterface.generated.h"

#define RESULT_OK							0 // ����
#define RESULT_USER_CANCELED				1 // ������ ��ҵǾ����ϴ�
#define RESULT_SERVICE_UNAVAILABLE			2 // �ܸ� �Ǵ� ���� ��Ʈ��ũ ������ �߻��Ͽ����ϴ�.
#define RESULT_BILLING_UNAVAILABLE			3 // ���� ó�� �������� ������ �߻��Ͽ����ϴ�.
#define RESULT_ITEM_UNAVAILABLE				4 // ��ǰ�� �Ǹ����� �ƴϰų� ������ �� ���� ��ǰ�Դϴ�.
#define RESULT_DEVELOPER_ERROR				5 // �ùٸ��� ���� ��û�Դϴ�.
#define RESULT_ERROR						6 // ���ǵ��� ���� ��Ÿ ������ �߻��߽��ϴ�.
#define RESULT_ITEM_ALREADY_OWNED			7 // �̹� �������� �����ϰ� �ֽ��ϴ�.
#define RESULT_ITEM_NOT_OWNED				8 // �������� �����ϰ� ���� �ʾ� �Һ��� �� �����ϴ�.
#define RESULT_FAIL							9 // ������ �����߽��ϴ�. ���� ���� ���� �� ���� ������ Ȯ�� �� �ٽ� �������ּ���.
#define RESULT_NEED_LOGIN					10 // ����� �� �α����� �ʿ��մϴ�.
#define RESULT_NEED_UPDATE					11 // ���� ����� ������Ʈ�� �ʿ��մϴ�.
#define RESULT_SECURITY_ERROR				12 // ������ �ۿ��� ������ ��û�Ǿ����ϴ�.
#define RESULT_BLOCKED_APP					13 // ��û�� ���ܵǾ����ϴ�
#define RESULT_NOT_SUPPORT_SANDBOX			14 // �׽�Ʈ ȯ�濡���� �������� �ʴ� ����Դϴ�.
#define ERROR_DATA_PARSING					1001 // ���� ������ �Ľ� ������ �߻��߽��ϴ�.
#define ERROR_SIGNATURE_VERIFICATION		1002 // ���������� ������� ������ �߻��߽��ϴ�.
#define ERROR_ILLEGAL_ARGUMENT				1003 // ���������� ���� �Ķ���Ͱ� �Է� �Ǿ����ϴ�.
#define ERROR_UNDEFINED_CODE				1004 // ���ǵ��� ���� ������ �߻��߽��ϴ�.
#define ERROR_SIGNATURE_NOT_VALIDATION		1005 // �Է��� ���̼��� Ű�� ��ȿ���� �ʽ��ϴ�.
#define ERROR_UPDATE_OR_INSTALL				1006 // ���� ��� ��ġ�� �����Ͽ����ϴ�.
#define ERROR_SERVICE_DISCONNECTED			1007 // ���� ������ ������ ���������ϴ�.
#define ERROR_FEATURE_NOT_SUPPORTED			1008 // ����� �������� �ʽ��ϴ�.
#define ERROR_SERVICE_TIMEOUT				1009 // ���񽺿� ����ϴ� �ð��� �ʰ��Ǿ����ϴ�.
#define RESULT_EMERGENCY_ERROR				99999 // ���� �������Դϴ�.

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


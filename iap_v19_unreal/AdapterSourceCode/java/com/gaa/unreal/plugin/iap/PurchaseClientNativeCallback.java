package com.gaa.unreal.plugin.iap;

import androidx.annotation.Nullable;

import com.gaa.sdk.iap.AcknowledgeListener;
import com.gaa.sdk.iap.ConsumeListener;
import com.gaa.sdk.iap.IapResult;
import com.gaa.sdk.iap.IapResultListener;
import com.gaa.sdk.iap.ProductDetail;
import com.gaa.sdk.iap.ProductDetailsListener;
import com.gaa.sdk.iap.PurchaseClient.ResponseCode;
import com.gaa.sdk.iap.PurchaseClientStateListener;
import com.gaa.sdk.iap.PurchaseData;
import com.gaa.sdk.iap.PurchasesListener;
import com.gaa.sdk.iap.PurchasesUpdatedListener;
import com.gaa.sdk.iap.RecurringProductListener;
import com.gaa.sdk.iap.StoreInfoListener;

import java.util.Collections;
import java.util.List;

public class PurchaseClientNativeCallback implements PurchaseClientStateListener,
        PurchasesUpdatedListener,
        ProductDetailsListener,
        PurchasesListener,
        ConsumeListener,
        AcknowledgeListener,
        RecurringProductListener,
        StoreInfoListener,
        IapResultListener {

    private final long futureHandle;

    public PurchaseClientNativeCallback() {
        this.futureHandle = 0;
    }

    public PurchaseClientNativeCallback(long futureHandle) {
        this.futureHandle = futureHandle;
    }

    // =============================================================================================
    // PurchaseClientStateListener
    // =============================================================================================
    @Override
    public void onSetupFinished(IapResult iapResult) {
        if (iapResult.isSuccess()) {
            nativeOnSetupFinished(futureHandle);
        } else {
            handleErrorCode(iapResult);
        }
    }

    @Override
    public void onServiceDisconnected() {
        nativeOnServiceDisconnected();
    }

    // =============================================================================================
    // PurchasesUpdatedListener
    // =============================================================================================

    @Override
    public void onPurchasesUpdated(IapResult iapResult, @Nullable List<PurchaseData> purchases) {
        if (iapResult.isSuccess()) {
            if (purchases == null) {
                purchases = Collections.emptyList();
            }
            String[] purchaseArray = new String[purchases.size()];
            String[] signatureArray = new String[purchases.size()];
            for (int i = 0; i < purchases.size(); i++) {
                PurchaseData p = purchases.get(i);
                purchaseArray[i] = p.getOriginalJson();
                signatureArray[i] = p.getSignature();
            }

            nativeOnPurchaseUpdated(purchaseArray, signatureArray, futureHandle);
        } else {
            handleErrorCode(iapResult);
        }
    }

    // =============================================================================================
    // ProductDetailsListener
    // =============================================================================================

    @Override
    public void onProductDetailsResponse(IapResult iapResult, @Nullable List<ProductDetail> productDetails) {
        if (iapResult.isSuccess()) {
            if (productDetails == null) {
                productDetails = Collections.emptyList();
            }
            String[] detailsArray = new String[productDetails.size()];
            for (int i = 0; i < productDetails.size(); i++) {
                detailsArray[i] = productDetails.get(i).getOriginalJson();
            }

            nativeOnProductDetailsResponse(detailsArray, futureHandle);
        } else {
            handleErrorCode(iapResult);
        }
    }

    // =============================================================================================
    // PurchasesListener
    // =============================================================================================

    @Override
    public void onPurchasesResponse(IapResult iapResult, @Nullable List<PurchaseData> purchases) {
        if (iapResult.isSuccess()) {
            if (purchases == null) {
                purchases = Collections.emptyList();
            }

            String[] purchaseArray = new String[purchases.size()];
            String[] signatureArray = new String[purchases.size()];
            for (int i = 0; i < purchases.size(); i++) {
                PurchaseData p = purchases.get(i);
                purchaseArray[i] = p.getOriginalJson();
                signatureArray[i] = p.getSignature();
            }

            nativeOnQueryPurchasesResponse(purchaseArray, signatureArray, futureHandle);
        } else {
            handleErrorCode(iapResult);
        }
    }

    // =============================================================================================
    // ConsumeListener
    // =============================================================================================

    @Override
    public void onConsumeResponse(IapResult iapResult, @Nullable PurchaseData purchaseData) {
        if (iapResult.isSuccess()) {
            nativeOnConsumePurchaseResponse(purchaseData.getOriginalJson(), futureHandle);
        } else {
            handleErrorCode(iapResult);
        }
    }

    // =============================================================================================
    // AcknowledgeListener
    // =============================================================================================

    @Override
    public void onAcknowledgeResponse(IapResult iapResult, @Nullable PurchaseData purchaseData) {
        if (iapResult.isSuccess()) {
            nativeOnAcknowledgePurchaseResponse(purchaseData.getOriginalJson(), futureHandle);
        } else {
            handleErrorCode(iapResult);
        }
    }

    // =============================================================================================
    // RecurringProductListener
    // =============================================================================================

    @Override
    public void onRecurringResponse(IapResult iapResult, @Nullable PurchaseData purchaseData, String action) {
        if (iapResult.isSuccess()) {
            nativeOnRecurringProductResponse(purchaseData.getOriginalJson(), action, futureHandle);
        } else {
            handleErrorCode(iapResult);
        }
    }

    // =============================================================================================
    // StoreInfoListener
    // =============================================================================================

    @Override
    public void onStoreInfoResponse(IapResult iapResult, String storeCode) {
        if (iapResult.isSuccess()) {
            nativeOnStoreInfoResponse(storeCode, futureHandle);
        } else {
            handleErrorCode(iapResult);
        }
    }

    // =============================================================================================
    // IapResultListener
    // =============================================================================================

    @Override
    public void onResponse(IapResult iapResult) {
        nativeOnIapResultResponse(iapResult.getResponseCode(), iapResult.getMessage(), futureHandle);
    }

    public void handleErrorCode(IapResult iapResult) {
        if (iapResult.getResponseCode() == ResponseCode.RESULT_NEED_LOGIN) {
            nativeOnNeedLogin();
        } else if (iapResult.getResponseCode() == ResponseCode.RESULT_NEED_UPDATE) {
            nativeOnNeedUpdate();
        } else {
            onResponse(iapResult);
        }
    }

    // =============================================================================================
    // native method
    // =============================================================================================

    // 원스토어 서비스와 연결이 성공한 경후 호출
    public static native void nativeOnSetupFinished(long futureHandle);

    // 원스토어 서비스와 연결이 시스템에 의해 끊어졌을 경우 호출
    public static native void nativeOnServiceDisconnected();

    // 결제 API(AndroidTrunkJava_GAALaunchPurchaseFlow)의 결제 성공 데이터 전달
    public static native void nativeOnPurchaseUpdated(String[] purchases, String[] signatures, long futureHandle);

    // 상품 상세 조회 API(AndroidTrunkJava_GAAQueryProductDetails)의 데이터 전달
    public static native void nativeOnProductDetailsResponse(String[] productDetails, long futureHandle);

    // 미소비 구매 이력 조회 API(AndroidTrunkJava_GAAQueryPurchasesAsync)의 데이터 전달
    public static native void nativeOnQueryPurchasesResponse(String[] purchases, String[] signatures, long futureHandle);

    // ConsumePurchase API(AndroidTrunkJava_GAAConsumeAsync)의 결과 값 전달
    public static native void nativeOnConsumePurchaseResponse(String purchaseData, long futureHandle);

    // AcknowledgePurchase API(AndroidTrunkJava_GAAAcknowledgeAsync)의 결과 값 전달
    public static native void nativeOnAcknowledgePurchaseResponse(String purchaseData, long futureHandle);

    // 월정액 상품 상태 변 API(AndroidTrunkJava_GAAManageRecurringProductAsync)의 결과 값 전달
    public static native void nativeOnRecurringProductResponse(String purchaseData, String action, long futureHandle);

    // 마켓 구분 코드 API(AndroidTrunkJava_GAAGetStoreInfoAsync)의 결과 값 전달
    public static native void nativeOnStoreInfoResponse(String storeCode, long futureHandle);

    // API 호출 시 error에 대한 결과 값 전달
    public static native void nativeOnIapResultResponse(int responseCode, String message, long futureHandle);

    // 원스토어 서비스 설치 및 업데이트 필요시 호출
    public static native void nativeOnNeedUpdate();

    // 원스토어 로그인 필요시 호출
    public static native void nativeOnNeedLogin();
}

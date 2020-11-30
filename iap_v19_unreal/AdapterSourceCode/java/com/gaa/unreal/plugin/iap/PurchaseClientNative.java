package com.gaa.unreal.plugin.iap;

import android.app.Activity;
import android.content.Context;
import android.os.Handler;

import com.gaa.sdk.iap.AcknowledgeParams;
import com.gaa.sdk.iap.ConsumeParams;
import com.gaa.sdk.iap.IapHelper;
import com.gaa.sdk.iap.IapResult;
import com.gaa.sdk.iap.ProductDetailsParams;
import com.gaa.sdk.iap.PurchaseClient;
import com.gaa.sdk.iap.PurchaseClient.ResponseCode;
import com.gaa.sdk.iap.PurchaseClientStateListener;
import com.gaa.sdk.iap.PurchaseData;
import com.gaa.sdk.iap.PurchaseFlowParams;
import com.gaa.sdk.iap.RecurringProductParams;

import org.json.JSONException;

import java.util.Arrays;
import java.util.List;


public class PurchaseClientNative {

    private boolean isServiceConnected;
    private PurchaseClient mPurchaseClient;

    public PurchaseClientNative(Context context, String public64EncodedKey) {
        mPurchaseClient = PurchaseClient.newBuilder(context)
                .setBase64PublicKey(public64EncodedKey)
                .setListener(new PurchaseClientNativeCallback())
                .build();
    }

    private void startConnection(final ServiceRunnable executeOnSuccess) {
        mPurchaseClient.startConnection(new PurchaseClientStateListener() {
            @Override
            public void onSetupFinished(final IapResult iapResult) {
                if (iapResult.isSuccess()) {
                    isServiceConnected = true;
                    if (executeOnSuccess != null) {
                        executeOnSuccess.run();
                    }
                    return;
                }
                executeOnSuccess.nativeCallback.handleErrorCode(iapResult);
            }

            @Override
            public void onServiceDisconnected() {
                isServiceConnected = false;
            }
        });
    }

    private void startConnectionForLogin(final ServiceRunnable executeOnSuccess) {
        mPurchaseClient.startConnection(new PurchaseClientStateListener() {
            @Override
            public void onSetupFinished(final IapResult iapResult) {
                if (iapResult.isSuccess() || iapResult.getResponseCode() == ResponseCode.RESULT_NEED_LOGIN) {
                    isServiceConnected = true;
                    if (executeOnSuccess != null) {
                        executeOnSuccess.run();
                    }
                    return;
                }
                executeOnSuccess.nativeCallback.handleErrorCode(iapResult);
            }

            @Override
            public void onServiceDisconnected() {
                isServiceConnected = false;
            }
        });
    }

    private void executeServiceRequest(ServiceRunnable runnable) {
        if (isServiceConnected) {
            runnable.run();
        } else {
            startConnection(runnable);
        }
    }

    private void executeServiceRequestForLogin(ServiceRunnable runnable) {
        if (isServiceConnected) {
            runnable.run();
        } else {
            startConnectionForLogin(runnable);
        }
    }

    public void startConnection(final long futureHandle) {
        startConnection(new ServiceRunnable(futureHandle) {
            @Override
            public void run() {
                IapResult iapResult = IapHelper.toIapResult(ResponseCode.RESULT_OK);
                nativeCallback.onSetupFinished(iapResult);
            }
        });
    }

    public void endConnection() {
        isServiceConnected = false;
        mPurchaseClient.endConnection();
    }

    public void launchPurchaseFlow(final Activity activity,
                                    final String productId,
                                    final String productType,
                                    final String productName,
                                    final String developerPayload,
                                    final String gameUserId,
                                    final boolean promotionApplicable) {

        executeServiceRequest(new ServiceRunnable() {
            @Override
            public void run() {
                PurchaseFlowParams params = PurchaseFlowParams.newBuilder()
                        .setProductId(productId)
                        .setProductType(productType)
                        .setProductName(productName)
                        .setDeveloperPayload(developerPayload)
                        .setGameUserId(gameUserId)
                        .setPromotionApplicable(promotionApplicable).build();
                mPurchaseClient.launchPurchaseFlow(activity, params);
            }
        });
    }

    public void consumeAsync(final String jsonPurchaseData, final String developerPayload, final long futureHandle) {
        executeServiceRequest(new ServiceRunnable(futureHandle) {
            @Override
            public void run() {
                try {
                    ConsumeParams params = ConsumeParams.newBuilder()
                            .setPurchaseData(new PurchaseData(jsonPurchaseData))
                            .setDeveloperPayload(developerPayload).build();
                    mPurchaseClient.consumeAsync(params, nativeCallback);
                } catch (JSONException e) {
                    nativeCallback.handleErrorCode(IapHelper.toIapResult(ResponseCode.ERROR_DATA_PARSING));
                }
            }
        });
    }

    public void acknowledgeAsync(final String jsonPurchaseData, final String developerPayload, final long futureHandle) {
        executeServiceRequest(new ServiceRunnable(futureHandle) {
            @Override
            public void run() {
                try {
                    AcknowledgeParams params = AcknowledgeParams.newBuilder()
                            .setPurchaseData(new PurchaseData(jsonPurchaseData))
                            .setDeveloperPayload(developerPayload).build();
                    mPurchaseClient.acknowledgeAsync(params, nativeCallback);
                } catch (JSONException e) {
                    nativeCallback.handleErrorCode(IapHelper.toIapResult(ResponseCode.ERROR_DATA_PARSING));
                }
            }
        });
    }

    public void queryPurchasesAsync(final String productType, final long futureHandle) {
        executeServiceRequest(new ServiceRunnable(futureHandle) {
            @Override
            public void run() {
                mPurchaseClient.queryPurchasesAsync(productType, nativeCallback);
            }
        });

    }

    public void queryProductDetails(final String[] productIds, final String productType, final long futureHandle) {
        executeServiceRequest(new ServiceRunnable(futureHandle) {
            @Override
            public void run() {
                try {
                    List<String> productIdList = Arrays.asList(productIds);
                    ProductDetailsParams params = ProductDetailsParams.newBuilder()
                            .setProductIdList(productIdList)
                            .setProductType(productType).build();
                    mPurchaseClient.queryProductDetailsAsync(params, nativeCallback);
                } catch (Exception e) {
                    nativeCallback.handleErrorCode(IapHelper.toIapResult(ResponseCode.RESULT_FAIL));
                }
            }
        });
    }

    public void manageRecurringProductAsync(final String jsonPurchaseData, final long futureHandle) {
        executeServiceRequest(new ServiceRunnable(futureHandle) {
            @Override
            public void run() {
                try {
                    RecurringProductParams params = RecurringProductParams.newBuilder()
                            .setPurchaseData(new PurchaseData(jsonPurchaseData)).build();
                    mPurchaseClient.manageRecurringProductAsync(params, nativeCallback);
                } catch (JSONException e) {
                    nativeCallback.handleErrorCode(IapHelper.toIapResult(ResponseCode.ERROR_DATA_PARSING));
                }
            }
        });
    }

    public void getStoreInfoAsync(final long futureHandle) {
        executeServiceRequest(new ServiceRunnable(futureHandle) {
            @Override
            public void run() {
                mPurchaseClient.getStoreInfoAsync(nativeCallback);
            }
        });
    }

    public void launchUpdateOrInstall(final Activity activity, final long futureHandle) {
        mPurchaseClient.launchUpdateOrInstallFlow(activity, new PurchaseClientNativeCallback(futureHandle));
    }

    public void launchLoginFlowAsync(final Activity activity, final long futureHandle) {
        executeServiceRequestForLogin(new ServiceRunnable() {
            @Override
            public void run() {
                mPurchaseClient.launchLoginFlowAsync(activity, new PurchaseClientNativeCallback(futureHandle));

            }
        });
    }


    private abstract static class ServiceRunnable implements Runnable {
        public PurchaseClientNativeCallback nativeCallback;

        ServiceRunnable() {
            nativeCallback = new PurchaseClientNativeCallback();
        }

        ServiceRunnable(long futureHandle) {
            nativeCallback = new PurchaseClientNativeCallback(futureHandle);
        }
    }
}

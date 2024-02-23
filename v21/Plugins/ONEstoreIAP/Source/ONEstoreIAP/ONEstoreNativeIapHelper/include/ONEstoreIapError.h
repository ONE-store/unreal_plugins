/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP {


enum class ResponseCode {
    // 성공
    RESULT_OK = 0,
    // 결제가 취소되었습니다.
    RESULT_USER_CANCELED,
    // 단말 또는 서버 네트워크 오류가 발생하였습니다.
    RESULT_SERVICE_UNAVAILABLE,
    // 구매 처리 과정에서 오류가 발생하였습니다.
    RESULT_BILLING_UNAVAILABLE,
    // 상품이 판매중이 아니거나 구매할 수 없는 상품입니다.
    RESULT_ITEM_UNAVAILABLE,
    // 올바르지 않은 요청입니다.
    RESULT_DEVELOPER_ERROR,
    // 정의되지 않은 기타 오류가 발생했습니다.
    RESULT_ERROR,
    // 이미 아이템을 소유하고 있습니다.
    RESULT_ITEM_ALREADY_OWNED,
    // 아이템을 소유하고 있지 않아 소비할 수 없습니다.
    RESULT_ITEM_NOT_OWNED,
    // 결제에 실패했습니다. 결제 가능 여부 및 결제 수단을 확인 후 다시 결제해주세요.
    RESULT_FAIL,
    // 스토어 앱 로그인이 필요합니다.
    RESULT_NEED_LOGIN,
    // 결제 모듈의 업데이트가 필요합니다.
    RESULT_NEED_UPDATE,
    // 비정상 앱에서 결제가 요청되었습니다.
    RESULT_SECURITY_ERROR,
    // 요청이 차단되었습니다.
    RESULT_BLOCKED_APP,
    // 테스트 환경에서는 지원하지 않는 기능입니다.
    RESULT_NOT_SUPPORT_SANDBOX,


    // 응답 데이터 파싱 오류가 발생했습니다.
    ERROR_DATA_PARSING = 1001,
    // 구매정보의 서명검증 에러가 발생했습니다.
    ERROR_SIGNATURE_VERIFICATION,
    // 정상적이지 않은 파라미터가 입력 되었습니다.
    ERROR_ILLEGAL_ARGUMENT,
    // 정의되지 않은 오류가 발생했습니다.
    ERROR_UNDEFINED_CODE,
    // 입력한 라이센스 키가 유효하지 않습니다.
    ERROR_SIGNATURE_NOT_VALIDATION,
    // 결제 모듈 설치에 실패하였습니다.
    ERROR_UPDATE_OR_INSTALL,
    // 결제 모듈과의 연결이 끊어졌습니다.
    ERROR_SERVICE_DISCONNECTED,
    // 기능을 지원하지 않습니다.
    ERROR_FEATURE_NOT_SUPPORTED,
    // 서비스와 통신하는 시간이 초과되었습니다.
    ERROR_SERVICE_TIMEOUT,
    // 원스토어에 연결할 수 없습니다. 원스토어 앱 실행이 필요합니다.
    ERROR_CLIENT_NOT_ENABLED,


    // 서버 점검중입니다
    RESULT_EMERGENCY_ERROR = 99999
};

}


#ifdef __cplusplus
}
#endif
/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_ALC {

enum class ResponseCode {
    RESULT_OK = 0,                      // 성공
    RESULT_UNKNOWN = -1,                // 알 수 없는 오류가 발생하였습니다.
    RESULT_USER_CANCELED = 1,           // 사용자가 로그인을 취소한 상태입니다.
    RESULT_SERVICE_UNAVAILABLE = 2,     // 단말 또는 서버 네트워크 오류가 발생하였습니다.
    RESULT_ALC_UNAVAILABLE = 3,         // ALC api 버전 정보가 낮은 상태입니다.
    RESULT_DEVELOPER_ERROR = 5,         // 파라미터가 유효하지 않은 상태입니다.
    RESULT_ERROR = 6,                   // 정의되지 않은 기타 오류가 발생하였습니다.
    RESULT_NEED_LOGIN = 10,             // 스토어 앱 로그인 필요합니다.
    RESULT_NEED_UPDATE = 11,            // 원스토어서비스를 업데이트 하거나 설치 해야 합니다.
    ERROR_SERVICE_UNAVAILABLE = 2000,   // 일시적인 서비스오류가 발생하였습니다.
    ERROR_SERVICE_TIMEOUT = 2100,       // 서비스 응답이 없습니다.
    ERROR_USER_LOGIN_CANCELED = 2101,   // 로그인을 취소하였습니다.
    ERROR_INSTALL_USER_CANCELED = 2103, // 원스토어 서비스 설치를 취소 하였습니다.
    ERROR_DATA_PARSING = 2001,          // 응답데이터 파싱 오류가 발생하였습니다.
    ERROR_SIGNATURE_VERIFICATION = 2002,// 라이선스 키가 맞지 않거나 구매 내역이 없는 유저 입니다.
    ERROR_NOT_FOREGROUND = 2104,        // 백그라운드 서비스에서는 진행할 수 없습니다.
    ERROR_CLIENT_NOT_ENABLED = 1010     // 원스토어에 연결할 수 없습니다. 원스토어 앱 실행이 필요합니다.
};

}

#ifdef __cplusplus
}
#endif
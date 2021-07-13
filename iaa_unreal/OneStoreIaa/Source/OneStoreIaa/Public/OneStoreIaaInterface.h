#pragma once

#define RESULT_OK							0 // 성공
#define RESULT_USER_CANCELED				1 // 취소되었습니다
#define RESULT_ERROR						6 // 정의되지 않은 기타 오류가 발생했습니다.
#define RESULT_FAIL							9 // 실패.
#define RESULT_NEED_LOGIN					10 // 스토어 앱 로그인이 필요합니다.
#define RESULT_NEED_UPDATE					11 // 모듈의 업데이트가 필요합니다.
#define RESULT_SECURITY_ERROR				12 // 비정상 앱에서 요청되었습니다.

#define ERROR_ILLEGAL_ARGUMENT				1003 // 정상적이지 않은 파라미터가 입력 되었습니다.
#define ERROR_UPDATE_OR_INSTALL				1006 // 모듈 설치에 실패하였습니다.
#define RESULT_EMERGENCY_ERROR				99999 // 서버 점검중입니다.

#define ONESTORE_REQUEST_OFFERWALL			800 

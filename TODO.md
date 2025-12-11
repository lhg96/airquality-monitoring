# 프로젝트 개선 체크리스트

**작성일**: 2025년 12월 11일  
**상태**: Phase 1 완료, Phase 2 진행 중

---

## ✅ Phase 1: 긴급 조치 (완료)

### 환경 정비
- [x] SDKMAN 설치
- [x] Java 8 (Zulu 8.0.432) 설치
- [x] 통합 .gitignore 생성
- [x] .env.example 환경 변수 템플릿 생성

### 문서화
- [x] ArimAirAirKoreaCrawler/README.md
- [x] ArimAirSerial/README.md
- [x] KTR_DUST_Cal/README.md
- [x] ArimAirGAE/README.md
- [x] 통합 README.md
- [x] PROJECT_ANALYSIS.md (프로젝트 분석 보고서)

### 보안 강화
- [x] .gitignore에 보안 파일 추가
- [x] 환경 변수 템플릿 생성

### 의존성 업데이트
- [x] ArimAirAirKoreaCrawler 의존성 업데이트
- [x] ArimAirSerial 의존성 업데이트
- [x] ArimAirGAEClient 의존성 업데이트

---

## 🔄 Phase 2: 코드 리팩토링 및 기술 부채 해결

### air-quality-crawler 리팩토링
- [x] **OpenCSV 5.9 API 변경 대응**
  - [x] `CsvValidationException` 예외 처리 추가
  - [x] CSV 읽기 로직 수정
  - [ ] 테스트 코드 작성
  
- [x] **환경 변수 적용**
  - [x] `application.properties`에서 하드코딩된 값 제거
  - [x] 환경 변수 사용 안내 추가
  - [ ] API 키를 환경 변수에서 로드하는 코드 구현
  
- [ ] **코드 구조 개선**
  - [ ] 패키지 구조 정리 (model, service, util 분리)
  - [ ] 상수 클래스 분리 (Constants.java)
  - [ ] 설정 클래스 분리 (Config.java)
  
- [ ] **로깅 개선**
  - [ ] logback.xml 설정 파일 추가
  - [ ] 적절한 로그 레벨 설정
  - [ ] 로그 포맷 표준화
  
- [ ] **에러 처리 강화**
  - [ ] Custom Exception 클래스 생성
  - [ ] Try-catch 블록 개선
  - [ ] API 호출 실패 시 재시도 로직

### ArimAirSerial 리팩토링
- [ ] **코드 구조 개선**
  - [ ] SerialPortManager 클래스 생성
  - [ ] 다중 포트 처리 추상화
  - [ ] 설정 파일로 COM 포트 관리
  
- [ ] **에러 처리**
  - [ ] 포트 연결 실패 시 자동 재연결
  - [ ] 타임아웃 설정
  - [ ] 예외 처리 강화
  
- [ ] **데이터 검증**
  - [ ] 센서 데이터 유효성 검사
  - [ ] 체크섬 검증 (가능한 경우)
  - [ ] 잘못된 데이터 필터링
  
- [ ] **테스트 코드**
  - [ ] 단위 테스트 작성
  - [ ] Mock 포트를 사용한 테스트

### KTR_DUST_Cal 리팩토링
- [ ] **설정 파일 외부화**
  - [ ] `config.properties` 파일 생성
  - [ ] 센서 파일명 설정 외부화
  - [ ] 임계값(upperThreshold, lowerThreshold) 외부화
  - [ ] 센서 개수 동적 설정
  
- [ ] **코드 구조 개선**
  - [ ] `CalibrationConfig` 클래스 생성
  - [ ] `SensorDataProcessor` 인터페이스 생성
  - [ ] `CSVReader`를 여러 클래스로 분리
    - [ ] `CSVReaderService`
    - [ ] `CalibrationService`
    - [ ] `AverageCalculator`
    - [ ] `SummaryGenerator`
  
- [ ] **메모리 효율성 개선**
  - [ ] 스트리밍 방식 CSV 처리 고려
  - [ ] 대용량 파일 처리 최적화
  - [ ] 메모리 사용량 모니터링
  
- [ ] **알고리즘 개선**
  - [ ] 2개 이상 센서 이상값 시 처리 로직
  - [ ] 가중치 평균 옵션 추가
  - [ ] 통계 정보 출력 강화
  
- [ ] **테스트 코드**
  - [ ] 보정 알고리즘 단위 테스트
  - [ ] 이동 평균 계산 테스트
  - [ ] 엣지 케이스 테스트

### ArimAirGAE 리팩토링
- [ ] **의존성 업데이트**
  - [ ] Google App Engine 버전 확인
  - [ ] Servlet API 최신화 검토
  - [ ] 보안 취약점 패치
  
- [ ] **코드 구조 개선**
  - [ ] DAO 패턴 구현 검증
  - [ ] Service 레이어 추가
  - [ ] DTO 클래스 정리
  
- [ ] **API 문서화**
  - [ ] Swagger/OpenAPI 스펙 추가
  - [ ] API 엔드포인트 문서화
  - [ ] 요청/응답 예제 추가
  
- [ ] **보안 강화**
  - [ ] JWT 토큰 인증 구현
  - [ ] CORS 설정
  - [ ] Rate Limiting
  
- [ ] **데이터베이스**
  - [ ] Connection Pool 설정
  - [ ] Transaction 관리
  - [ ] SQL Injection 방지

### air-quality-client 리팩토링
- [ ] **테스트 코드 정리**
  - [ ] JUnit 테스트로 전환
  - [ ] Mock 서버 사용
  - [ ] 통합 테스트 추가
  
- [ ] **API 클라이언트 개선**
  - [ ] RestTemplate 또는 OkHttp 고려
  - [ ] 재시도 로직 추가
  - [ ] 에러 처리 개선

### air-quality-calibration 리팩토링
- [x] **설정 외부화**
  - [x] config.properties 파일 생성
  - [x] config.properties.example 템플릿 생성
  - [x] CSVReader에서 설정 파일 읽기 로직 구현
  - [x] 하드코딩된 파일명 제거
  
- [ ] **코드 구조 개선**
  - [ ] ConfigurationManager 클래스 분리
  - [ ] CalibrationService 클래스 분리
  - [ ] 센서 데이터 처리 로직 모듈화
  
- [ ] **테스트 코드 추가**
  - [ ] 단위 테스트 작성
  - [ ] 보정 알고리즘 검증

---

## 🏗️ Phase 3: 공통 모듈 및 아키텍처 개선

### 공통 라이브러리 생성
- [ ] **airmonitoring-common 모듈**
  - [ ] `arim.common.model` 패키지
    - [ ] AirData 공통 모델
    - [ ] SensorInfo 모델
    - [ ] ApiResponse 모델
  - [ ] `arim.common.util` 패키지
    - [ ] DateUtils
    - [ ] ValidationUtils
    - [ ] MathUtils
  - [ ] `arim.common.csv` 패키지
    - [ ] CSVReader (공통)
    - [ ] CSVWriter (공통)
  - [ ] `arim.common.exception` 패키지
    - [ ] AirMonitoringException
    - [ ] DataValidationException
    - [ ] SensorConnectionException

### Git 설정 개선
- [ ] **Git LFS 설정**
  ```bash
  git lfs install
  git lfs track "*.csv"
  ```
- [ ] **대용량 CSV 파일 처리**
  - [ ] .gitattributes 파일 생성
  - [ ] 기존 CSV 파일 LFS로 마이그레이션
  
- [ ] **Submodule 업데이트 스크립트**
  ```bash
  # update-submodules.sh
  git submodule update --remote --merge
  ```

### 빌드 자동화
- [ ] **build-all.sh 스크립트 작성**
  ```bash
  #!/bin/bash
  # 전체 프로젝트 빌드 스크립트
  ```
- [ ] **Maven 멀티 모듈 프로젝트 검토**
  - [ ] 부모 pom.xml 생성 고려
  - [ ] 의존성 버전 통합 관리
  
- [ ] **CI/CD 준비**
  - [ ] GitHub Actions 워크플로우 작성
  - [ ] 빌드 자동화
  - [ ] 테스트 자동화

---

## 📊 Phase 4: 데이터베이스 및 아키텍처 전환

### 데이터베이스 도입
- [ ] **시계열 DB 선택**
  - [ ] InfluxDB vs TimescaleDB vs MongoDB 비교
  - [ ] POC 프로젝트 진행
  - [ ] 성능 테스트
  
- [ ] **스키마 설계**
  - [ ] air_quality_data 테이블
  - [ ] device_info 테이블
  - [ ] sensor_calibration 테이블
  - [ ] 인덱스 설계
  
- [ ] **마이그레이션 도구**
  - [ ] CSV to DB 마이그레이션 스크립트
  - [ ] 데이터 검증 도구
  - [ ] 백업 및 복구 전략

### 마이크로서비스 아키텍처
- [ ] **서비스 분리 설계**
  - [ ] Data Collection Service
  - [ ] Serial Communication Service
  - [ ] Calibration Service
  - [ ] Storage Service
  - [ ] API Gateway Service
  
- [ ] **메시지 큐 도입**
  - [ ] Apache Kafka 또는 RabbitMQ 선택
  - [ ] Topic/Queue 설계
  - [ ] Producer/Consumer 구현
  
- [ ] **컨테이너화**
  - [ ] 각 서비스별 Dockerfile 작성
  - [ ] docker-compose.yml 작성
  - [ ] Kubernetes 배포 준비

### 실시간 처리 파이프라인
- [ ] **Kafka Streams 구현**
  - [ ] 실시간 데이터 수집
  - [ ] 실시간 보정 처리
  - [ ] 실시간 평균 계산
  
- [ ] **모니터링**
  - [ ] Prometheus 메트릭 수집
  - [ ] Grafana 대시보드 구성
  - [ ] 알림 시스템 구축

---

## 🧪 Phase 5: 테스트 및 품질 보증

### 테스트 전략
- [ ] **단위 테스트**
  - [ ] JUnit 5 설정
  - [ ] Mockito 설정
  - [ ] 코드 커버리지 > 80% 목표
  
- [ ] **통합 테스트**
  - [ ] Testcontainers 사용
  - [ ] 데이터베이스 통합 테스트
  - [ ] API 통합 테스트
  
- [ ] **성능 테스트**
  - [ ] JMeter 시나리오 작성
  - [ ] 부하 테스트
  - [ ] 병목 구간 분석

### 코드 품질
- [ ] **정적 분석**
  - [ ] SonarQube 설정
  - [ ] PMD, FindBugs 설정
  - [ ] 코드 스타일 가이드 적용
  
- [ ] **보안 스캔**
  - [ ] OWASP Dependency Check
  - [ ] 취약점 스캔
  - [ ] 보안 패치 자동화

---

## 🚀 Phase 6: 고도화 및 AI/ML

### 머신러닝 기반 이상값 탐지
- [ ] **데이터 준비**
  - [ ] 학습 데이터셋 준비
  - [ ] 특성 엔지니어링
  - [ ] 데이터 정규화
  
- [ ] **모델 개발**
  - [ ] Isolation Forest 모델 학습
  - [ ] LSTM 예측 모델 학습
  - [ ] 모델 평가 및 검증
  
- [ ] **모델 배포**
  - [ ] 모델 서빙 API
  - [ ] 실시간 예측
  - [ ] 모델 모니터링

### 대시보드 개발
- [ ] **Grafana 대시보드**
  - [ ] 실시간 PM2.5 그래프
  - [ ] 센서별 비교 차트
  - [ ] 이상값 알림 패널
  - [ ] 보정 전/후 비교
  
- [ ] **커스텀 웹 대시보드**
  - [ ] React 프론트엔드
  - [ ] WebSocket 실시간 통신
  - [ ] 반응형 디자인
  - [ ] 차트 라이브러리 (Chart.js, D3.js)

### 모바일 앱
- [ ] **React Native 앱**
  - [ ] 실시간 공기질 조회
  - [ ] 위치 기반 측정소 검색
  - [ ] 푸시 알림
  - [ ] 히스토리 조회

### AI 예측 모델
- [ ] **기상 데이터 통합**
  - [ ] 기상청 API 연동
  - [ ] 데이터 전처리
  
- [ ] **교통량 데이터 통합**
  - [ ] 교통정보 API 연동
  - [ ] 상관관계 분석
  
- [ ] **예측 모델**
  - [ ] 24시간 PM2.5 예측
  - [ ] 구역별 히트맵
  - [ ] 정확도 개선

---

## 📅 우선순위 및 일정

### High Priority (즉시 ~ 1주일)
1. [ ] OpenCSV API 변경 대응 (ArimAirAirKoreaCrawler)
2. [ ] 환경 변수 적용 (전체)
3. [ ] 로깅 설정 파일 추가
4. [ ] Git LFS 설정
5. [ ] 빌드 자동화 스크립트

### Medium Priority (1~2주)
6. [ ] KTR_DUST_Cal 설정 외부화
7. [ ] 코드 구조 개선 (패키지 분리)
8. [ ] 공통 모듈 생성
9. [ ] 단위 테스트 작성
10. [ ] API 문서화

### Low Priority (2~4주)
11. [ ] 데이터베이스 POC
12. [ ] 컨테이너화 (Docker)
13. [ ] CI/CD 파이프라인
14. [ ] 통합 테스트
15. [ ] 성능 최적화

### Future (1개월 이후)
16. [ ] 마이크로서비스 전환
17. [ ] 실시간 스트리밍 파이프라인
18. [ ] ML 기반 이상값 탐지
19. [ ] 웹 대시보드
20. [ ] 모바일 앱

---

## 📝 작업 진행 기록

### 2025-12-11 (완료)
- ✅ Java 8 환경 설정
- ✅ 통합 .gitignore 생성
- ✅ 환경 변수 템플릿 생성
- ✅ 전체 프로젝트 README.md 작성
- ✅ 의존성 버전 업데이트

### 다음 작업 (예정)
- ⏳ OpenCSV API 변경 대응
- ⏳ 환경 변수 적용
- ⏳ Git LFS 설정
- ⏳ 빌드 자동화 스크립트

---

## 🎯 성공 지표 (KPI)

### 기술 지표
- [ ] 코드 커버리지 > 80%
- [ ] 빌드 성공률 > 95%
- [ ] 평균 응답 시간 < 200ms
- [ ] 시스템 가용성 > 99.5%
- [ ] 기술 부채 감소 50%

### 데이터 품질 지표
- [ ] 이상값 탐지율 > 90%
- [ ] 보정 정확도 > 95%
- [ ] 데이터 손실률 < 0.1%

### 운영 지표
- [ ] 센서 데이터 수집 지연 < 1분
- [ ] 보정 처리 시간 < 5분
- [ ] API 에러율 < 1%
- [ ] 배포 빈도 증가
- [ ] 평균 장애 복구 시간(MTTR) 감소

---

**마지막 업데이트**: 2025년 12월 11일

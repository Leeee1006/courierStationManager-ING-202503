#include"tendencypredict.h"

/* 简易线性回归: y = a + bx */
void countPendingPackages(List* packages, time_t startDate, int* counts) {
    // 生成7天时间范围（含输入日期的当天）
    time_t dayStarts[7] = { 0 };
    struct tm start_tm;
    localtime_s(&start_tm, &startDate);

    for (int i = 0; i < 7; i++) {
        struct tm tmp = start_tm;
        tmp.tm_mday += i;
        tmp.tm_hour = 0;
        tmp.tm_min = 0;
        tmp.tm_sec = 0;
        mktime(&tmp);  // 自动处理跨月/年
        dayStarts[i] = mktime(&tmp);
    }

    // 统计包裹
    
    for (ListNode* current = packages->head->next; current != NULL; current = current->next) {
        Package* pkg = (Package*)current->data;
        struct tm tm_pending;
        localtime_s(&tm_pending, &pkg->time.pending);

        // 转换为当天0点时间戳
        tm_pending.tm_hour = 0;
        tm_pending.tm_min = 0;
        tm_pending.tm_sec = 0;
        time_t pendingDay = mktime(&tm_pending);

        // 匹配统计范围
        for (int i = 0; i < 7; i++) {
            if (pendingDay == dayStarts[i]) {
                counts[i]++;
                break;
            }
        }
    }
}
// 严格日期验证函数
bool validateDate(int year, int month, int day) {
    // 基础范围校验
    if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // 各月份天数验证
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29; // 闰年2月

    }

    return day <= daysInMonth[month - 1];
}

bool inputDateSafe(time_t* result) {
    char dateStr[11] = { 0 }; // 修改为字符数组
    printf("请输入起始日期（格式：YYYY-MM-DD）: ");
    if (scanf_s("%10s", dateStr, (unsigned)_countof(dateStr)) != 1) {
        fprintf(stderr, "错误：读取输入失败\n");
        return false;
    }

    int year, month, day;
    if (sscanf_s(dateStr, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        fprintf(stderr, "错误：日期格式无效\n");
        return false;
    }

    if (!validateDate(year, month, day)) {
        fprintf(stderr, "错误：非法日期值\n");
        return false;
    }

    struct tm tm = { 0 };
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_isdst = -1;

    *result = mktime(&tm);
    if (*result == -1) {
        fprintf(stderr, "错误：时间转换失败\n");
        return false;
    }

    // 验证转换结果与输入一致
    struct tm verify_tm;
    localtime_s(&verify_tm, result);
    if (verify_tm.tm_year + 1900 != year ||
        verify_tm.tm_mon + 1 != month ||
        verify_tm.tm_mday != day) {
        fprintf(stderr, "错误：日期自动调整无效\n");
        return false;
    }

    return true;
}
void linearRegression(const double x[], const double y[], int n, double* a, double* b)
{
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXX = 0.0;
    for (int i = 0; i < n; i++)
    {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumXX += x[i] * x[i];
    }
    double veragex = sumX / n;
    double veragey = sumY / n;
    double denominator = sumXX - veragex * veragex * n;
    if (denominator == 0.0)
    {
        *b = 0.0;
        *a = 0.0;
        return;
    }
    *b = (sumXY - n * veragex * veragey) / denominator;  // 斜率
    *a = (sumY - (*b) * sumX) / n;                 // 截距
}

/* 绘制ASCII折线图，o表示实际值，x表示预测值 */
void drawAsciiChart(const double x[], const double y[], const double yPred[], int n)
{
    /* 找最大y值，用于设置图表高度 */
    double maxY = y[0];
    for (int i = 1; i < n; i++)
    {
        if (y[i] > maxY)
        {
            maxY = y[i];
        }
        if (yPred[i] > maxY)
        {
            maxY = yPred[i];
        }
    }
    int height = (int)maxY + 1;
    double minY = y[0];
    for (int i = 1; i < n; i++)
    {
        if (y[i] < minY)
        {
            minY = y[i];
        }
        if (yPred[i] < minY)
        {
            minY = yPred[i];
        }
    }
    int lowest = (int)minY - 1;

    /* 从上往下打印每一行 */
    for (int row = height; row >= lowest; row--)
    {
        printf("%3d | ", row);
        /* 每列对应一个数据点 */
        for (int col = 0; col < n; col++)
        {
            int actual = (int)(y[col] + 0.5);
            int pred = (int)(yPred[col] + 0.5);
            if (row == actual && row == pred)
            {
                printf("* ");  /* 重合 */
            }
            else if (row == actual)
            {
                printf("o ");  /* 实际值 */
            }
            else if (row == pred)
            {
                printf("x ");  /* 预测值 */
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }

    /* 打印X轴刻度 */
    printf("    +");
    for (int i = 0; i < n; i++)
    {
        printf("--");
    }
    printf("\n      ");
    for (int i = 0; i < n; i++)
    {
        printf("%.0f ", x[i]);
    }
    printf("\n");
}
//
//int main()
//{
//    /* 过去7天的入库数(示例)，可扩展到出库数与滞留件数 */
//    double inbound[DAYS] = { 10, 12, 15, 18, 16, 20, 22 };
//    /* x代表第几天(1~7) */
//    double xData[DAYS] = { 1, 2, 3, 4, 5, 6, 7 };
//
//    /* 线性回归求斜率b与截距a */
//    double a = 0.0, b = 0.0;
//    linearRegression(xData, inbound, DAYS, &a, &b);
//
//    /* 计算过去7天的预测值，用于在ASCII图中对比 */
//    double yPred[DAYS];
//    for (int i = 0; i < DAYS; i++) {
//        yPred[i] = a + b * xData[i];
//    }
//
//    printf("回归方程(入库 y) = %.2f + %.2f * x\n\n", a, b);
//
//    /* 打印过去7天(实际 vs 预测)的ASCII折线图 */
//    drawAsciiChart(xData, inbound, yPred, DAYS);
//
//    /* 预测未来7天(第8~14天)的入库量总和 */
//    double sumNextWeek = 0.0;
//    for (int day = 8; day <= 14; day++)
//    {
//        double predValue = a + b * day;
//        sumNextWeek += predValue;
//        printf("Day %2d => 预测入库: %.2f\n", day, predValue);
//    }
//    printf("\n未来一周入库总量预测: %.2f\n", sumNextWeek);
//
//    return 0;
//}



//
//void countPendingPackages(Package* head, time_t startDate, int* counts) {
//    // 生成7天时间范围（含输入日期的当天）
//    time_t dayStarts[7];
//    struct tm start_tm;
//    localtime_s(&start_tm, &startDate);
//
//    for (int i = 0; i < 7; i++) {
//        struct tm tmp = start_tm;
//        tmp.tm_mday += i;
//        tmp.tm_hour = 0;
//        tmp.tm_min = 0;
//        tmp.tm_sec = 0;
//        mktime(&tmp);  // 自动处理跨月/年
//        dayStarts[i] = mktime(&tmp);
//    }
//
//    // 统计包裹
//    Package* current = head;
//    while (current != NULL) {
//        struct tm tm_pending;
//        localtime_s(&tm_pending, &current->time.pending);
//
//        // 转换为当天0点时间戳
//        tm_pending.tm_hour = 0;
//        tm_pending.tm_min = 0;
//        tm_pending.tm_sec = 0;
//        time_t pendingDay = mktime(&tm_pending);
//
//        // 匹配统计范围
//        for (int i = 0; i < 7; i++) {
//            if (pendingDay == dayStarts[i]) {
//                counts[i]++;
//                break;
//            }
//        }
//        current = current->next;
//    }
//}
//
//int main() {
//    time_t startDate;
//    if (!inputDateSafe(&startDate)) {
//        fprintf(stderr, "程序终止：日期输入无效\n");
//        system("pause");
//        return EXIT_FAILURE;
//    }
//
//    // 示例数据初始化
//    Package pkg1, pkg2;
//    strcpy_s(pkg1.trackingNum, _countof(pkg1.trackingNum), "PKG001");
//    strcpy_s(pkg2.trackingNum, _countof(pkg2.trackingNum), "PKG002");
//
//    struct tm tm_tmp = { 0 };
//    localtime_s(&tm_tmp, &startDate);
//
//    // 包裹1：当天下午时间
//    tm_tmp.tm_hour = 14;
//    pkg1.time.pending = mktime(&tm_tmp);
//    pkg1.next = &pkg2;
//
//    // 包裹2：第二天上午时间
//    tm_tmp.tm_mday++;
//    tm_tmp.tm_hour = 9;
//    mktime(&tm_tmp); // 标准化时间
//    pkg2.time.pending = mktime(&tm_tmp);
//    pkg2.next = NULL;
//
//    // 执行统计
//    int counts[7] = { 0 };
//    countPendingPackages(&pkg1, startDate, counts);
//
//    // 输出结果
//    printf("\n%-8s%-12s%s\n", "天数", "日期", "入库量");
//    struct tm current_tm;
//    for (int i = 0; i < 7; i++) {
//        time_t day = startDate + i * 86400;
//        localtime_s(&current_tm, &day);
//        printf("Day%-2d  %04d-%02d-%02d   %d\n",
//            i + 1,
//            current_tm.tm_year + 1900,
//            current_tm.tm_mon + 1,
//            current_tm.tm_mday,
//            counts[i]);
//    }
//
//    system("pause");
//    return EXIT_SUCCESS;
//}
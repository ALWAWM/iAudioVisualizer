#ifndef iAV_Ver
#define iAV_Ver "0.3.7.2"
#define iAV_Minimum_Compatible_Version "0.3.5"
#include "commonheaders.h"
using namespace std;
// 解析版本号字符串
tuple<int, int, int, int, string> parseVersion(const string& version) {
    int major = 0, minor = 0, patch = 0, build = 0;
    char preRelease[20] = ""; // 用于存储预发布标签
    int parsedItems = sscanf(version.c_str(), "%d.%d.%d.%d-%19s", &major, &minor, &patch, &build, preRelease);

    // 如果只解析到四个部分，preRelease 保持为空字符串
    if (parsedItems < 5) {
        preRelease[0] = '\0';
    }
    return make_tuple(major, minor, patch, build, string(preRelease));
}
auto version=parseVersion(iAV_Ver);
// 比较版本号
bool isVersionGreaterOrEqual(const string& version1, const string& version2) {
    auto [major1, minor1, patch1, build1, preRelease1] = parseVersion(version1);
    auto [major2, minor2, patch2, build2, preRelease2] = parseVersion(version2);

    if (major1 != major2) return major1 > major2;
    if (minor1 != minor2) return minor1 > minor2;
    if (patch1 != patch2) return patch1 > patch2;
    if (build1 != build2) return build1 > build2;
    return true;
}

bool isVersionInRange(const string& version, const string& minVersion, const string& maxVersion) {
    return isVersionGreaterOrEqual(version, minVersion) && isVersionGreaterOrEqual(maxVersion,version);
}
#endif //iAV_Ver
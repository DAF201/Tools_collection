# bocchi the rock as example, just don't use this, need to look up the stream origin manually which is annoying
import aiohttp
import asyncio

URL = '''
https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-12-02A6C81188qf2.mp4/media_%s.ts?dnvodendtime=1673683490&dnvodhash=9RpnaSLBkQqd0uKBvsOZreJwbbpY6AKdApdEDHK3od4=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=f137fffb8f7ecfa41d0bd82a05555f4e&us=1&vv=7f81b83782d721b6d8f490a98da3a8f2&pub=CJOtCpKnC3OvC2uoD3KsCLyggQzDpOkCJCpBZ4pCYunD35VP34tOsKqCsGqC3XZD3CmEM4sOsPaC68uCpbYPMLYE3bVPJarDMOoEMOmCJKpPc5aOc5bDZ0pDc9YPJXZEJ4pCc2
'''


async def main():
    for x in range(200):
        try:
            async with aiohttp.ClientSession() as session:
                async with session.get(URL % str(x)) as resp:
                    data = bytearray()
                    while True:
                        chunk = await resp.content.read(100)
                        if not chunk:
                            break
                        data += chunk
                        with open('episode_12/%s.ts' % x, 'wb') as ts:
                            ts.write(data)
        except Exception as e:
            print(e)
            break

asyncio.run(main())

# with open("episode_12.mp4", 'wb')as final:
#     for x in range(1000):
#         try:
#             with open('episode_12\%s.ts' % str(x), 'rb')as ts:
#                 final.write(ts.read())
#         except:
#             break
            
# I don't know how long does this last or does it have some kind of keep-alive things, but just for an idea

# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-1-0104B308Cf2dx.mp4/media_%s.ts?dnvodendtime=1673675345&dnvodhash=YQKIRs5QsSmpjrUks9pWUQyqT4L3ScGswBJh7F2aoZ0=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=d14302907576238da0ba91dce35156fc&us=1&vv=24d56d7af068ba783f06e0578356562a&pub=CJOtCpKmCZKqDIuoDpKrCbyggQzDpOkCJCpBZ4pCYunD35VCpDbDMKrDcPaC3KsD39YOZXYDJWnCJ5aDJOtC3PcC31VOp9ZPZaoOs4mOpKmP3LaEJWmOM5YCM8rPJ0uE3KrCZ6
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-2-01E90E2F63te0.mp4/media_%s.ts?dnvodendtime=1673677803&dnvodhash=ehZJUB9a2IhhmQ3HkjNWnnB3tqj6XZrT7v5lLo5FJ80=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=056a158ef50ea5af52a800f1725ccea4&us=1&vv=776c064d5c71ebd734170a2c383fe6e8&pub=CJOtCpKmCZKqDIuoDpKrCbyggQzDpOkCJCpBZ4pCYunD35VCpDbDMKrDcPaC3KsD39YOZXYDJWnCJ5aDJOtC3PcC31VOp9ZPZaoOs4mOpKmP3LaEJWmOM5YCM8rPJ0uE3KrCZ6
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-3-028DD788Asc1r.mp4/media_%s.ts?dnvodendtime=1673678348&dnvodhash=o_SiLok_Cu4DMJgeeWHcJDvbHHYfNma7gWQlYrxRe6A=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=09a8512bcf5c0f6ae4e3e82f3d802086&us=1&vv=e6e48068ff1b41df7e49a3d88df59946&pub=CJOtCpKmCZKqDIuoDpKrCbyggQzDpOkCJCpBZ4pCYunD35VCpDbDMKrDcPaC3KsD39YOZXYDJWnCJ5aDJOtC3PcC31VOp9ZPZaoOs4mOpKmP3LaEJWmOM5YCM8rPJ0uE3KrCZ6
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-04-02C4F52D1.mp4/media_%s.ts?dnvodendtime=1673678683&dnvodhash=Z3N6f-bSowlGey-WvLylPrgeV7ui97dw57Yck1qAFB4=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=e4dca2eee9048d6e9cc1725a3c6a13b2&us=1&vv=5240213274476047c888e4e872c32a51&pub=CJOtCpKmDJWuCoumD34qNrLJNpSsBZ4pCounCp8kCJGnNp8rEJPaPJSnCZSrPJGuOJXXOcDbCsCnCpGrOZCvE31aNpTaP68nDJTXDZKmC31YDcGtOpLZOp4vPMLZDJ9bEMHc
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-5-00A606C93u09m.mp4/media_%s.ts?dnvodendtime=1673679001&dnvodhash=HzI59C-T_tEFYNBe6Xj4oRpnu0HT3AAsZtUld4x3h_U=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=e5fb1c7ac951aa0c5363d420f00c94a6&us=1&vv=1084aca2792cec065ab4a5ed2a5086f5&pub=CJOtCpKmDJWuCoumD34qNrLJNpSsBZ4pCounCp8kCJGnNp8rEJPaPJSnCZSrPJGuOJXXOcDbCsCnCpGrOZCvE31aNpTaP68nDJTXDZKmC31YDcGtOpLZOp4vPMLZDJ9bEMHc
# https://s8-e1.dnvodcdn.me/ppot/_definst_/mp4:s8/kvod/dhp-gdyg-06-036CBE010.mp4/media_%s.ts?dnvodendtime=1673679730&dnvodhash=djoqMK5CE4ltDX-8JcHsUWfMgLVPgHJ70yN_ymyF8CA=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=ca624f91f88fe4cfff0c62dd99be9974&us=1&vv=a6eeeab6c96040a5ed12653390b7762e&pub=CJOtCpKmDJWuCoumD34qNrLJNpSsBZ4pCounCp8kCJGnNp8rEJPaPJSnCZSrPJGuOJXXOcDbCsCnCpGrOZCvE31aNpTaP68nDJTXDZKmC31YDcGtOpLZOp4vPMLZDJ9bEMHc
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-7-02BE3DA5Fjc1t.mp4/media_%s.ts?dnvodendtime=1673680312&dnvodhash=Lj1b8-VCGJGyg5n2ddhPgW_oppmaymZOS0RmR-Nsj6Q=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=c3dc150c0f98667e3f647255b6f89cfa&us=1&vv=2f7e835d81f09cea1b3864b6b1181524&pub=CJOtCpKmDp8vCourEJ4qELyggQzDpOkCJCpBZ4pCYunD35VEJGnPJGqE6OrOZWuD30oDJbZP68sD3TaPJ8sCZ9ZDZTVOpapD6DbOJXaC3SsOsLaCM8tPZ8mCM8vOMHaEMGmPZ3
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-8-00B51E187xg3p.mp4/media_%s.ts?dnvodendtime=1673680979&dnvodhash=zciC1JSw1HJOLkdoYVosDK9pwwV9H-y_bGKgDuIy8r0=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=4a90b65e803085cc800328d734e6385c&us=1&vv=728e67514419f0d59edba40827de7299&pub=CJOtCpKmE34tEIunDJCsE5yggQzDpOkCJCpBZ4pCYunD35VOp1XPc9XDp4pCs8rD3KuD3WoP3CqOZCoDJCoDJPZOJXVCJSrP6CsOpCtEJ5bOJKoDZ4uCp4rDpSvDZamOZ9bOJ8
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-9-02FBFA6D28fyz.mp4/media_%s.ts?dnvodendtime=1673681628&dnvodhash=4rQwtPeZYUmsZ3SZNw2a9QE2S7fVSWi80Imi-LlVS_4=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=4b86878c3fd221d5258656cc7e3d9320&us=1&vv=26c0de376aadc904354c3cbbd8659e20&pub=CJOtCpKmE3WoDousD3SmD5yggQzDpOkCJCpBZ4pCYunD35VC3WnE31cP3KuD3bYD6DcC65cOcGtCJKqCZOqE35ZCpLVOJCoOpCqOs5XOJLXE64pD3bXOsDYC65aE30qPZKpPJ4
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-10-011CCDC774yz8.mp4/media_%s.ts?dnvodendtime=1673682479&dnvodhash=J6GGw4tHRbA3EyVQaeluQ-xvggUSC4E3wBSrM7vYj9s=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=aa05d91a0d03cbe72d75298e3538bb1a&us=1&vv=0f8f42f399076c451effb7de3f4dd3d8&pub=CJOtCpKmEJOtE2uqC3StDbyggQzDpOkCJCpBZ4pCYunD35VCZatCpWtOs9aCJamD3CsP64uCMGmDp9aCsDbD3KtCZHVEJTbC3KoOMKmEJGmPMPaOJ4pCZDaCJOrEMCqDJCpP39
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-11-01357798Ce7ut.mp4/media_%s.ts?dnvodendtime=1673683099&dnvodhash=5RjsO_y5tBh2peIJijeCqBjX3qtqy9OpqfcgXbSCEL4=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=2831be892655c8455b864c65b06c9fd5&us=1&vv=e131b990304b2fd60cf9527ad4efdcbf&pub=CJOtCpKnC38vE2usDpKoE5yggQzDpOkCJCpBZ4pCYunD35VOJOrCsGpE6LbOpbaD6KpDJatCJOnCpSrOMOqCJSvEJ1VC3OoDp4qP35XOJ5XE3amP30tEJDbOZPYDsHbPZCnD32
# https://s10-e1.dnvodcdn.me/ppot/_definst_/mp4:s10/hvod/dhp-gdyg-12-02A6C81188qf2.mp4/media_%s.ts?dnvodendtime=1673683490&dnvodhash=9RpnaSLBkQqd0uKBvsOZreJwbbpY6AKdApdEDHK3od4=&dnvodCustomParameter=0_76.133.132.141.US_1&lb=f137fffb8f7ecfa41d0bd82a05555f4e&us=1&vv=7f81b83782d721b6d8f490a98da3a8f2&pub=CJOtCpKnC3OvC2uoD3KsCLyggQzDpOkCJCpBZ4pCYunD35VP34tOsKqCsGqC3XZD3CmEM4sOsPaC68uCpbYPMLYE3bVPJarDMOoEMOmCJKpPc5aOc5bDZ0pDc9YPJXZEJ4pCc2

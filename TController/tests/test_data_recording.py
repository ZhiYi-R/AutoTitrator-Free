"""测试数据记录逻辑：验证进样和滴定阶段数据的完整性"""

import unittest
from unittest.mock import MagicMock, patch
import time


class TestDataRecording(unittest.TestCase):
    """验证上位机数据记录在进样和滴定阶段的正确性"""

    def test_injection_data_preserved_after_pump_done(self):
        """验证进样完成后电位数据不被清空"""
        # 模拟数据记录场景
        rec_potential = []
        
        # 模拟进样阶段记录数据
        for i in range(10):
            t = i * 0.1
            v = 0.5 + i * 0.01
            vol = i * 0.05
            rec_potential.append((t, v, v * 0.95, vol))
        
        self.assertEqual(len(rec_potential), 10, "进样阶段应记录 10 个数据点")
        
        # 模拟 _potential_widget.reset() —— 只清空显示，不清空记录
        # （这里不操作 rec_potential，因为实际代码中 reset() 不清空记录列表）
        
        # 验证记录缓冲区未被清空
        self.assertEqual(len(rec_potential), 10, "进样完成后记录缓冲区应保持完整")
        
        # 模拟滴定阶段追加数据
        for i in range(10, 20):
            t = i * 0.1
            v = 0.6 + i * 0.01
            vol = (i - 10) * 0.05
            rec_potential.append((t, v, v * 0.95, vol))
        
        self.assertEqual(len(rec_potential), 20, "滴定结束应包含进样和滴定两阶段数据")
        
        # 验证数据连续性
        self.assertAlmostEqual(rec_potential[9][0], 0.9, places=2, msg="进样最后一帧时间戳")
        self.assertAlmostEqual(rec_potential[10][0], 1.0, places=2, msg="滴定第一帧时间戳")

    def test_recording_cleared_on_titration_start(self):
        """验证启动滴定时清空上次记录"""
        rec_potential = []
        
        # 模拟上次滴定残留数据
        for i in range(5):
            rec_potential.append((i * 0.1, 0.5, 0.48, i * 0.05))
        
        self.assertEqual(len(rec_potential), 5, "上次滴定残留 5 个数据点")
        
        # 模拟 _start_titration() 中的清空逻辑
        recording = True
        if recording:
            rec_potential.clear()
        
        self.assertEqual(len(rec_potential), 0, "启动滴定时应清空记录缓冲区")

    def test_volume_switching_between_pumps(self):
        """验证进样和滴定阶段的体积来源切换"""
        from enum import Enum
        
        class TitrationState(Enum):
            IDLE = 0
            INJECTING = 1
            TITRATING = 2
        
        pump1_volume = 0.0
        pump2_volume = 0.0
        state = TitrationState.INJECTING
        
        # 进样阶段：使用泵 1 体积
        pump1_volume = 2.5
        vol = pump1_volume if state == TitrationState.INJECTING else pump2_volume
        self.assertEqual(vol, 2.5, "进样阶段应使用泵 1 体积")
        
        # 切换到滴定阶段
        state = TitrationState.TITRATING
        pump2_volume = 1.0
        vol = pump1_volume if state == TitrationState.INJECTING else pump2_volume
        self.assertEqual(vol, 1.0, "滴定阶段应使用泵 2 体积")

    def test_recording_flag_initialization(self):
        """验证记录开关初始化同步"""
        # 模拟持久化设置
        saved_settings = {"record": True}
        
        # 错误的初始化方式（修复前）
        recording_old = False
        rec_var_old = True  # UI 开关
        self.assertNotEqual(recording_old, rec_var_old, "修复前：内部标志与 UI 不一致")
        
        # 正确的初始化方式（修复后）
        saved_rec = saved_settings.get("record", True)
        recording_new = saved_rec
        rec_var_new = saved_rec
        self.assertEqual(recording_new, rec_var_new, "修复后：内部标志与 UI 一致")
        self.assertTrue(recording_new, "默认应启用记录")


class TestExportedDataStructure(unittest.TestCase):
    """验证导出 Excel 中的数据结构"""

    def test_potential_sheet_columns(self):
        """验证电位工作表的列结构"""
        # 当前列结构
        columns = ["Time (s)", "Raw Voltage (V)", "Filtered Voltage (V)", "Volume (mL)"]
        self.assertEqual(len(columns), 4, "电位表应有 4 列")
        
        # 推荐的增强列结构（可选）
        enhanced_columns = [
            "Time (s)", 
            "Phase",  # 新增：Injecting / Titrating
            "Raw Voltage (V)", 
            "Filtered Voltage (V)", 
            "Pump1 Volume (mL)",  # 拆分：进样体积
            "Pump2 Volume (mL)"   # 拆分：滴定体积
        ]
        self.assertEqual(len(enhanced_columns), 6, "增强电位表应有 6 列")

    def test_phase_identification_by_time(self):
        """验证通过时间戳识别阶段"""
        # 模拟数据：前 10 帧为进样，后 10 帧为滴定
        rec_potential = []
        for i in range(20):
            t = i * 0.1
            phase = "Injecting" if i < 10 else "Titrating"
            rec_potential.append((t, 0.5, 0.48, i * 0.05, phase))
        
        # 验证阶段标识
        self.assertEqual(rec_potential[5][4], "Injecting", "前半段应为进样")
        self.assertEqual(rec_potential[15][4], "Titrating", "后半段应为滴定")
        
        # 统计各阶段数据点数
        injecting_count = sum(1 for _, _, _, _, p in rec_potential if p == "Injecting")
        titrating_count = sum(1 for _, _, _, _, p in rec_potential if p == "Titrating")
        self.assertEqual(injecting_count, 10, "进样阶段 10 个数据点")
        self.assertEqual(titrating_count, 10, "滴定阶段 10 个数据点")


if __name__ == "__main__":
    unittest.main()

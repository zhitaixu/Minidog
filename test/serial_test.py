#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
串口通信测试脚本
用于测试机器人的串口命令功能
"""

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    print("错误: 未安装pyserial库")
    print("请运行: pip install pyserial")
    import sys
    sys.exit(1)

import time
import sys

def list_available_ports():
    """列出所有可用的串口"""
    ports = serial.tools.list_ports.comports()
    if not ports:
        print("未找到可用的串口设备")
        return []
    
    print("可用的串口设备:")
    for i, port in enumerate(ports, 1):
        print(f"  {i}. {port.device} - {port.description}")
    return ports

def test_serial_communication(port='COM3', baudrate=9600):
    """
    测试串口通信功能
    
    Args:
        port (str): 串口端口名称
        baudrate (int): 波特率
    """
    try:
        # 连接串口
        print(f"正在连接串口 {port}...")
        ser = serial.Serial(port, baudrate, timeout=2)
        time.sleep(3)  # 等待连接建立和系统启动
        
        print("串口连接成功！")
        print("开始测试串口命令...")
        
        # 测试命令列表
        test_commands = [
            ('h', '帮助信息'),
            ('s', '状态查询'),
            ('1', '前进'),
            ('2', '左转'),
            ('3', '右转'),
            ('4', '后退'),
            ('5', '左上举手'),
            ('6', '右上举手'),
            ('7', '躺下'),
            ('8', '坐下'),
            ('10', '睡觉')
        ]
        
        for cmd, description in test_commands:
            print(f"\n--- 测试命令: {cmd} ({description}) ---")
            
            # 发送命令
            ser.write((cmd + '\n').encode())
            print(f"已发送命令: {cmd}")
            
            # 等待响应
            time.sleep(1)
            
            # 读取响应
            if ser.in_waiting:
                response = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                print(f"收到响应: {response.strip()}")
            
            # 等待动作完成（对于动作命令）
            if cmd.isdigit():
                print("等待动作完成...")
                time.sleep(3)
        
        print("\n所有测试命令执行完成！")
        
    except serial.SerialException as e:
        print(f"串口连接失败: {e}")
        print("请检查:")
        print("1. 串口端口名称是否正确")
        print("2. 设备是否已连接")
        print("3. 是否有其他程序占用串口")
        
    except KeyboardInterrupt:
        print("\n测试被用户中断")
        
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("串口连接已关闭")

def interactive_mode(port='COM3', baudrate=9600):
    """
    交互式模式，允许用户手动输入命令
    
    Args:
        port (str): 串口端口名称
        baudrate (int): 波特率
    """
    try:
        print(f"正在连接串口 {port}...")
        ser = serial.Serial(port, baudrate, timeout=2)
        time.sleep(3)
        
        print("串口连接成功！")
        print("进入交互式模式，输入命令控制机器人")
        print("输入 'quit' 或 'exit' 退出")
        print("输入 'help' 查看帮助")
        
        while True:
            try:
                # 获取用户输入
                cmd = input("\n请输入命令: ").strip()
                
                if cmd.lower() in ['quit', 'exit', 'q']:
                    print("退出交互式模式")
                    break
                    
                if cmd.lower() == 'help':
                    print("可用命令:")
                    print("  1 - 前进")
                    print("  2 - 左转")
                    print("  3 - 右转")
                    print("  4 - 后退")
                    print("  5 - 左上举手")
                    print("  6 - 右上举手")
                    print("  7 - 躺下")
                    print("  8 - 坐下")
                    print("  10 - 睡觉")
                    print("  s/status - 状态查询")
                    print("  h/help - 帮助信息")
                    continue
                
                if not cmd:
                    continue
                
                # 发送命令
                ser.write((cmd + '\n').encode())
                print(f"已发送命令: {cmd}")
                
                # 等待响应
                time.sleep(0.5)
                
                # 读取响应
                if ser.in_waiting:
                    response = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                    print(f"响应: {response.strip()}")
                
            except KeyboardInterrupt:
                print("\n退出交互式模式")
                break
                
    except serial.SerialException as e:
        print(f"串口连接失败: {e}")
        
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("串口连接已关闭")

def main():
    """主函数"""
    print("=== 机器人串口通信测试工具 ===")
    print()
    
    # 显示可用串口
    available_ports = list_available_ports()
    if not available_ports:
        print("请检查串口设备连接")
        return
    
    # 获取串口端口
    if len(sys.argv) > 1:
        port = sys.argv[1]
    else:
        print("\n可用串口:")
        for i, port_info in enumerate(available_ports, 1):
            print(f"  {i}. {port_info.device} - {port_info.description}")
        
        try:
            choice = input("\n请选择串口编号 (或直接输入端口名称): ").strip()
            if choice.isdigit() and 1 <= int(choice) <= len(available_ports):
                port = available_ports[int(choice) - 1].device
            else:
                port = choice if choice else 'COM3'
        except (ValueError, IndexError):
            port = input("请输入串口端口 (默认: COM3): ").strip() or 'COM3'
    
    print(f"使用串口端口: {port}")
    print()
    
    # 选择模式
    print("请选择模式:")
    print("1. 自动测试模式 (执行所有命令)")
    print("2. 交互式模式 (手动输入命令)")
    
    while True:
        choice = input("请输入选择 (1 或 2): ").strip()
        
        if choice == '1':
            test_serial_communication(port)
            break
        elif choice == '2':
            interactive_mode(port)
            break
        else:
            print("无效选择，请输入 1 或 2")

if __name__ == "__main__":
    main() 
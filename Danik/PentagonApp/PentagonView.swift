import UIKit

class PentagonView: UIView {
    
    var fillColor = UIColor.systemBlue
    
    override func draw(_ rect: CGRect) {
        guard let context = UIGraphicsGetCurrentContext() else { return }
        
        let center = CGPoint(x: bounds.midX, y: bounds.midY)
        let radius: CGFloat = min(bounds.width, bounds.height) / 2.5
        let path = UIBezierPath()
        
        for i in 0..<5 {
            let angle = CGFloat(i) * .pi * 2 / 5 - .pi / 2
            let point = CGPoint(x: center.x + cos(angle) * radius,
                                y: center.y + sin(angle) * radius)
            if i == 0 {
                path.move(to: point)
            } else {
                path.addLine(to: point)
            }
        }
        path.close()
        
        fillColor.setFill()
        path.fill()
    }
}

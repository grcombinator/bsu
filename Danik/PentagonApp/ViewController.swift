import UIKit

class ViewController: UIViewController {
    
    private let pentagonView = PentagonView()
    private var currentAnimation: CABasicAnimation?
    
    private let segmentedControl: UISegmentedControl = {
        let control = UISegmentedControl(items: ["Нет", "Масштаб", "Перемещение", "Скругление"])
        control.selectedSegmentIndex = 0
        control.addTarget(self, action: #selector(animationChanged(_:)), for: .valueChanged)
        return control
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Линейный градиентный фон
        let gradientLayer = CAGradientLayer()
        gradientLayer.frame = view.bounds
        gradientLayer.colors = [UIColor.systemTeal.cgColor, UIColor.systemPurple.cgColor]
        gradientLayer.startPoint = CGPoint(x: 0, y: 0)
        gradientLayer.endPoint = CGPoint(x: 1, y: 1)
        view.layer.insertSublayer(gradientLayer, at: 0)
        
        setupPentagon()
        setupUI()
    }
    
    private func setupPentagon() {
        pentagonView.backgroundColor = .clear
        pentagonView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(pentagonView)
        
        NSLayoutConstraint.activate([
            pentagonView.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            pentagonView.centerYAnchor.constraint(equalTo: view.centerYAnchor),
            pentagonView.widthAnchor.constraint(equalToConstant: 150),
            pentagonView.heightAnchor.constraint(equalToConstant: 150)
        ])
    }
    
    private func setupUI() {
        segmentedControl.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(segmentedControl)
        
        NSLayoutConstraint.activate([
            segmentedControl.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 20),
            segmentedControl.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20),
            segmentedControl.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20)
        ])
    }
    
    @objc private func animationChanged(_ sender: UISegmentedControl) {
        removeCurrentAnimation()
        
        switch sender.selectedSegmentIndex {
        case 1:
            scaleAnimation()
        case 2:
            moveAnimation()
        case 3:
            cornerAnimation()
        default:
            break
        }
    }
    
    private func removeCurrentAnimation() {
        if let anim = currentAnimation {
            pentagonView.layer.removeAnimation(forKey: anim.keyPath ?? "")
        }
    }
    
    private func scaleAnimation() {
        let anim = CABasicAnimation(keyPath: "transform.scale")
        anim.fromValue = 1.0
        anim.toValue = 1.5
        anim.duration = 1.0
        anim.autoreverses = true
        anim.repeatCount = .infinity
        pentagonView.layer.add(anim, forKey: nil)
        currentAnimation = anim
    }
    
    private func moveAnimation() {
        let anim = CABasicAnimation(keyPath: "position.x")
        anim.fromValue = pentagonView.center.x
        anim.toValue = pentagonView.center.x + 100
        anim.duration = 2.0
        anim.autoreverses = true
        anim.repeatCount = .infinity
        pentagonView.layer.add(anim, forKey: nil)
        currentAnimation = anim
    }
    
    private func cornerAnimation() {
        let anim = CABasicAnimation(keyPath: "cornerRadius")
        anim.fromValue = 0
        anim.toValue = 30
        anim.duration = 1.0
        anim.autoreverses = true
        anim.repeatCount = .infinity
        pentagonView.layer.add(anim, forKey: nil)
        currentAnimation = anim
    }
}
